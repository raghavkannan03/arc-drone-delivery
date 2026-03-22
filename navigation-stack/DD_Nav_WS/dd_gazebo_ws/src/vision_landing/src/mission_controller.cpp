#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_status.hpp>
#include <std_msgs/msg/float64.hpp>
#include <cmath>

enum class State {
  TAKEOFF,
  SEARCH,
  APPROACH,
  DESCEND,
  LANDED
};

class MissionController : public rclcpp::Node
{
public:
  MissionController() : Node("mission_controller"), state_(State::TAKEOFF)
  {
    pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
      "/landing_target_pose", 10,
      std::bind(&MissionController::pose_callback, this, std::placeholders::_1));

    status_sub_ = this->create_subscription<px4_msgs::msg::VehicleStatus>(
      "/fmu/out/vehicle_status", rclcpp::QoS(10).best_effort(),
      std::bind(&MissionController::status_callback, this, std::placeholders::_1));

    setpoint_pub_ = this->create_publisher<px4_msgs::msg::TrajectorySetpoint>(
      "/fmu/in/trajectory_setpoint", 10);

    offboard_pub_ = this->create_publisher<px4_msgs::msg::OffboardControlMode>(
      "/fmu/in/offboard_control_mode", 10);

    command_pub_ = this->create_publisher<px4_msgs::msg::VehicleCommand>(
      "/fmu/in/vehicle_command", 10);

    gimbal_pub_ = this->create_publisher<std_msgs::msg::Float64>(
      "/gimbal_tilt_cmd", 10);

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(50),
      std::bind(&MissionController::control_loop, this));

    tag_detected_ = false;
    tag_x_ = 0.0;
    tag_y_ = 0.0;
    tag_z_ = 0.0;
    search_angle_ = 0.0;
    offboard_counter_ = 0;
    armed_ = false;
    current_z_ = -5.0;

    RCLCPP_INFO(this->get_logger(), "Mission controller started");
  }

private:
  void pose_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
  {
    tag_detected_ = true;
    tag_x_ = msg->pose.position.x;
    tag_y_ = msg->pose.position.y;
    tag_z_ = msg->pose.position.z;
    RCLCPP_INFO(this->get_logger(), "Tag detected at x=%.2f y=%.2f z=%.2f",
      tag_x_, tag_y_, tag_z_);
  }

  void status_callback(const px4_msgs::msg::VehicleStatus::SharedPtr msg)
  {
    armed_ = (msg->arming_state == 2);
  }

  void publish_offboard_mode()
  {
    px4_msgs::msg::OffboardControlMode msg;
    msg.position = true;
    msg.velocity = false;
    msg.acceleration = false;
    msg.attitude = false;
    msg.body_rate = false;
    msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
    offboard_pub_->publish(msg);
  }

  void arm()
  {
    px4_msgs::msg::VehicleCommand cmd;
    cmd.command = px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM;
    cmd.param1 = 1.0;
    cmd.target_system = 1;
    cmd.target_component = 1;
    cmd.source_system = 1;
    cmd.source_component = 1;
    cmd.from_external = true;
    cmd.timestamp = this->get_clock()->now().nanoseconds() / 1000;
    command_pub_->publish(cmd);
    RCLCPP_INFO(this->get_logger(), "Arm command sent");
  }

  void set_offboard_mode()
  {
    px4_msgs::msg::VehicleCommand cmd;
    cmd.command = px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_SET_MODE;
    cmd.param1 = 1.0;
    cmd.param2 = 6.0;
    cmd.target_system = 1;
    cmd.target_component = 1;
    cmd.source_system = 1;
    cmd.source_component = 1;
    cmd.from_external = true;
    cmd.timestamp = this->get_clock()->now().nanoseconds() / 1000;
    command_pub_->publish(cmd);
    RCLCPP_INFO(this->get_logger(), "Offboard mode command sent");
  }

  void publish_setpoint(float x, float y, float z)
  {
    px4_msgs::msg::TrajectorySetpoint msg;
    msg.position[0] = x;
    msg.position[1] = y;
    msg.position[2] = z;
    msg.yaw = 0.0;
    msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
    setpoint_pub_->publish(msg);
  }

  void control_loop()
  {
    publish_offboard_mode();

    if (offboard_counter_ < 100) {
      publish_setpoint(0.0, 0.0, -5.0);
      offboard_counter_++;
      if (offboard_counter_ == 50) {
        set_offboard_mode();
        arm();
      }
      return;
    }

    switch (state_) {
      case State::TAKEOFF: {
        publish_setpoint(0.0, 0.0, -5.0);
        if (!armed_) {
          offboard_counter_++;
          if (offboard_counter_ % 40 == 0) {
            set_offboard_mode();
            arm();
            RCLCPP_INFO(this->get_logger(), "Retrying arm/offboard (attempt %d)", offboard_counter_ / 40);
          }
          RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
            "TAKEOFF: waiting to arm...");
        } else {
          state_ = State::SEARCH;
          RCLCPP_INFO(this->get_logger(), "Armed! Switching to SEARCH");
        }
        break;
      }

      case State::SEARCH: {
        search_angle_ += 0.05;
        if (search_angle_ > 1.5707) search_angle_ = -1.5707;

        std_msgs::msg::Float64 gimbal_msg;
        gimbal_msg.data = search_angle_;
        gimbal_pub_->publish(gimbal_msg);

        publish_setpoint(0.0, 0.0, -5.0);
        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
          "SEARCH: scanning for AprilTag");

        if (tag_detected_) {
          state_ = State::APPROACH;
          RCLCPP_INFO(this->get_logger(), "Tag found! Switching to APPROACH");
        }
        break;
      }

      case State::APPROACH: {
        publish_setpoint(tag_x_, tag_y_, -5.0);
        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
          "APPROACH: flying to tag at x=%.2f y=%.2f", tag_x_, tag_y_);

        double xy_dist = std::sqrt(tag_x_ * tag_x_ + tag_y_ * tag_y_);
        if (xy_dist < 0.3) {
          state_ = State::DESCEND;
          RCLCPP_INFO(this->get_logger(), "Aligned! Switching to DESCEND");
        } else if (!tag_detected_) {
          state_ = State::SEARCH;
          RCLCPP_INFO(this->get_logger(), "Tag lost! Switching back to SEARCH");
        }

        tag_detected_ = false;
        break;
      }

      case State::DESCEND: {
        current_z_ += 0.05;
        if (current_z_ > 0.0) current_z_ = 0.0;

        publish_setpoint(tag_x_, tag_y_, current_z_);
        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
          "DESCEND: z=%.2f", current_z_);

        if (current_z_ >= -0.1) {
          state_ = State::LANDED;
          RCLCPP_INFO(this->get_logger(), "LANDED!");
        }
        break;
      }

      case State::LANDED: {
        publish_setpoint(tag_x_, tag_y_, 0.0);
        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 5000,
          "LANDED on AprilTag");
        break;
      }
    }
  }

  State state_;
  bool tag_detected_;
  float tag_x_, tag_y_, tag_z_;
  double search_angle_;
  int offboard_counter_;
  bool armed_;
  float current_z_;

  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
  rclcpp::Subscription<px4_msgs::msg::VehicleStatus>::SharedPtr status_sub_;
  rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr setpoint_pub_;
  rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_pub_;
  rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr command_pub_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr gimbal_pub_;
  //rclcpp::Timer::SharedPtr timer_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MissionController>());
  rclcpp::shutdown();
  return 0;
}
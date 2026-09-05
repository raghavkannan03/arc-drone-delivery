#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
extern "C" {
#include <apriltag/apriltag.h>
#include <apriltag/tag36h11.h>
#include <apriltag/apriltag_pose.h>
}

class AprilTagDetector : public rclcpp::Node
{
public:
  AprilTagDetector() : Node("apriltag_detector")
  {
    td_ = apriltag_detector_create();
    tf_ = tag36h11_create();
    apriltag_detector_add_family(td_, tf_);
    td_->quad_decimate = 2.0;
    td_->nthreads = 4;

    sub_ = this->create_subscription<sensor_msgs::msg::Image>(
      "/zed/zed_node/rgb/image_rect_color", 10,
      std::bind(&AprilTagDetector::image_callback, this, std::placeholders::_1));

    pub_ = this->create_publisher<geometry_msgs::msg::PoseArray>("/tag_detections", 10);

    RCLCPP_INFO(this->get_logger(), "AprilTag detector started");
  }

  ~AprilTagDetector()
  {
    apriltag_detector_destroy(td_);
    tag36h11_destroy(tf_);
  }

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
  {
    cv::Mat frame;
    try {
      frame = cv_bridge::toCvCopy(msg, "bgr8")->image;
    } catch (cv_bridge::Exception & e) {
      RCLCPP_ERROR(this->get_logger(), "cv_bridge error: %s", e.what());
      return;
    }

    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    image_u8_t im = {
      .width = gray.cols,
      .height = gray.rows,
      .stride = gray.cols,
      .buf = gray.data
    };

    zarray_t * detections = apriltag_detector_detect(td_, &im);

    geometry_msgs::msg::PoseArray pose_array;
    pose_array.header = msg->header;

    for (int i = 0; i < zarray_size(detections); i++) {
      apriltag_detection_t * det;
      zarray_get(detections, i, &det);
      RCLCPP_INFO(this->get_logger(), "Detected tag ID: %d", det->id);

      geometry_msgs::msg::Pose pose;
      pose.position.x = det->c[0];
      pose.position.y = det->c[1];
      pose_array.poses.push_back(pose);
    }

    pub_->publish(pose_array);
    apriltag_detections_destroy(detections);
  }

  apriltag_detector_t * td_;
  apriltag_family_t * tf_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
  rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr pub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AprilTagDetector>());
  rclcpp::shutdown();
  return 0;
}

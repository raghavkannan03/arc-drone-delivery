cmake_minimum_required(VERSION 3.8)
project(vision_landing)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(px4_msgs REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include/vision_landing)

add_executable(apriltag_detector src/apriltag_detector.cpp)
ament_target_dependencies(apriltag_detector rclcpp sensor_msgs geometry_msgs cv_bridge OpenCV)
target_link_libraries(apriltag_detector apriltag)

add_executable(pose_estimator src/pose_estimator.cpp)
ament_target_dependencies(pose_estimator rclcpp geometry_msgs cv_bridge OpenCV tf2_ros)
target_link_libraries(pose_estimator apriltag)      

add_executable(landing_controller src/landing_controller.cpp)
ament_target_dependencies(landing_controller rclcpp geometry_msgs px4_msgs)

add_executable(mission_controller src/mission_controller.cpp)
ament_target_dependencies(mission_controller rclcpp geometry_msgs px4_msgs std_msgs)

add_executable(vio_node src/vio_node.cpp)
ament_target_dependencies(vio_node rclcpp sensor_msgs px4_msgs cv_bridge OpenCV)

install(TARGETS
  apriltag_detector
  pose_estimator
  landing_controller
  mission_controller
  vio_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

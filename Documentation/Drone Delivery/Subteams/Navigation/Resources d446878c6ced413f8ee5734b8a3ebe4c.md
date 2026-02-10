# Resources

[Localization (1)](Resources/Localization%20(1)%20a48724f65f0547988a363e0bef460a36.md)

[ROS VMs](Resources/ROS%20VMs%20eb8d2b2525e7434692a3f1c34d090110.md)

[DD_Nav_WS](Resources/DD_Nav_WS%20fd09e9d851dd440f878da854978af649.md)

[DD-LIO Plan](Resources/DD-LIO%20Plan%2011ad0747f56480bcbc9cd7a809c97451.md)

[DD-Nav2 Plan](Resources/DD-Nav2%20Plan%2011ed0747f564802f8ea3ca274ef57184.md)

[Revised Plan for Odometry System](Resources/Revised%20Plan%20for%20Odometry%20System%20189d0747f56480cebbdafe2744544f30.md)

# Github

[GitHub - purdue-arc/DD-obstacle-avoidance](https://github.com/purdue-arc/DD-obstacle-avoidance)

# Other

C++ Learning: [https://www.learncpp.com/](https://www.learncpp.com/)

**Good Resources to download:**

ROS Nav 2: [https://navigation.ros.org/getting_started/index.html](https://navigation.ros.org/getting_started/index.html)

- We plan on using ROS 2 Humble and in particular its navigation 2 stack to control the drone

**ROS2 Useful Commands:** 

- Command for launching a ros launch file: ros2 launch pkg_name launchfilename.launch.py
- If you want to build only 1 certain package with colcon: colcon build —packages-select package_filepath
- ros2 launch dd_gazebo simulation.launch.py

**Learning ROS2:** [https://docs.ros.org/en/rolling/Tutorials.html](https://docs.ros.org/en/rolling/Tutorials.html)

**Learning NAV2:** [https://navigation.ros.org/concepts/index.html](https://navigation.ros.org/concepts/index.html)

# Obstacle Avoidance

Pos: [https://dev.intelrealsense.com/docs/rs-pose](https://dev.intelrealsense.com/docs/rs-pose)
Pos-Prediction: [https://dev.intelrealsense.com/docs/rs-pose-predict](https://dev.intelrealsense.com/docs/rs-pose-predict) 
Dynamic Obstacle Avoidance: [https://ieeexplore.ieee.org/abstract/document/8491889](https://ieeexplore.ieee.org/abstract/document/8491889)
D* Algorithms: [https://drive.google.com/file/d/1XcB0w0IvobgjAYehDYUqe3qoPYX0miRA/view](https://drive.google.com/file/d/1XcB0w0IvobgjAYehDYUqe3qoPYX0miRA/view)
OA Records: [https://sites.google.com/view/pu-arc-dd-oa/home](https://sites.google.com/view/pu-arc-dd-oa/home)

VisDrone Dataset: [https://github.com/VisDrone/VisDrone-Dataset](https://github.com/VisDrone/VisDrone-Dataset)

# Obstacle Detection

Open CV: [https://docs.opencv.org/4.x/](https://docs.opencv.org/4.x/)
Stereo Vision & Lidar: [https://ieeexplore.ieee.org/document/4795550](https://ieeexplore.ieee.org/document/4795550)
Intel RealSense Library: [https://github.com/IntelRealSense/librealsense/tree/master](https://github.com/IntelRealSense/librealsense/tree/master)
RealSense with Python: [https://dev.intelrealsense.com/docs/python2](https://dev.intelrealsense.com/docs/python2)

# Long Term Navigation

Octomap Structure: [https://github.com/margaridaCF/FlyingOctomap_code](https://github.com/margaridaCF/FlyingOctomap_code)
Importing 3D Models: [https://wirewhiz.com/read-gltf-files/](https://wirewhiz.com/read-gltf-files/)
Point Cloud to OctoMap: [http://www.open3d.org/docs/latest/tutorial/geometry/octree.html](http://www.open3d.org/docs/latest/tutorial/geometry/octree.html)
OctoTree Generator: [https://github.com/purdue-arc/dd-octree_generator](https://github.com/purdue-arc/dd-octree_generator)
Cesium 3D tile server for storing obstacle data in gltf format: [https://github.com/3DGISKing/CesiumJs3DTileServer](https://github.com/3DGISKing/CesiumJs3DTileServer)

[OpenStreetMap obstacle data pipeline](Resources/OpenStreetMap%20obstacle%20data%20pipeline%20dadc4ef7d732451a9bc61935eecfeef2.md)

[Photogrammetry obstacle data pipeline](Resources/Photogrammetry%20obstacle%20data%20pipeline%20d4369255eff14e2a9a6186e532a91fcd.md)

[Adding OSM-based geospatial data to Gazebo](Resources/Adding%20OSM-based%20geospatial%20data%20to%20Gazebo%2092c9a8920a164b688668d113e3e44ed7.md)

# Localization

GPS: 

- [https://www.u-blox.com/en/product/neo-m9n-module](https://www.u-blox.com/en/product/neo-m9n-module)
- [https://navigation.ros.org/tutorials/docs/navigation2_with_gps.html](https://navigation.ros.org/tutorials/docs/navigation2_with_gps.html)

SLAM Algorithm: 

- Vi-SLAM:
    - [https://nvidia-isaac-ros.github.io/repositories_and_packages/isaac_ros_visual_slam/isaac_ros_visual_slam/index.html](https://nvidia-isaac-ros.github.io/repositories_and_packages/isaac_ros_visual_slam/isaac_ros_visual_slam/index.html)
        - This algorithm configures uses Isaac Sim as the simulation environment for testing but Isaac Sim is only configured for ground robots currently. You can look at either the Pegasuss simulator or Omni drone extensions, but currently, they do not suit our purposes. It requires Nvidia GPUs to run.
    - [https://docs.openvins.com/pages.html](https://docs.openvins.com/pages.html)
        - Seems to be more for research purposes, and it is hard to configure. It most likely would have problems being used in a production drone. Can use Nvidia GPUs.
    - [https://github.com/matlabbe/rtabmap_drone_example/blob/master/src/offboard_node.cpp](https://github.com/matlabbe/rtabmap_drone_example/blob/master/src/offboard_node.cpp)
        - Solid algorithm, it has some problems with speed or accuracy, but it can configure with gazebo and rviz; however, it uses ROS1. It has an active community. It also requires Nvidia GPUs to run
- Lidar-SLAM:
    - [https://github.com/SteveMacenski/slam_toolbox](https://github.com/SteveMacenski/slam_toolbox)
        - It see[ms](https://navigation.ros.org/development_guides/involvement_docs/index.html) to be the most production-ready SLAM algorithm as it integrates with the ROS Nav2 stack(https://navigation.ros.org/development_guides/involvement_docs/index.html), and it has optimizations for lifelong/continuous environment mapping. The drawback is that it requires LIDAR, which is much more expensive than a visual camera. It does not seem to need Nvidia GPUs to run.

# Flight Control

Bezier Curve Generation

- [https://github.com/caslabuiowa/OptimalBezierTrajectoryGeneration](https://github.com/caslabuiowa/OptimalBezierTrajectoryGeneration)
- [https://stackoverflow.com/a/21642962](https://stackoverflow.com/a/21642962)

Pixhawk

[https://github.com/pixhawk/Pixhawk-Standards](https://github.com/pixhawk/Pixhawk-Standards)

PX4

- [https://px4.io/](https://px4.io/)
- [https://docs.px4.io/main/en/getting_started/px4_basic_concepts.html](https://docs.px4.io/main/en/getting_started/px4_basic_concepts.html)
- [https://docs.px4.io/main/en/flight_modes/offboard.html](https://docs.px4.io/main/en/flight_modes/offboard.html)
- [https://docs.px4.io/main/en/ros/ros2_offboard_control.html](https://docs.px4.io/main/en/ros/ros2_offboard_control.html)
- [https://github.com/MShkut/JetsonNano-ROS2-PX4-Holybro-X500-V2/blob/3f28189c21d102e2add8f19fbc2d26098dbbd087/Serial Comms - Jetson Nano %26 PX4-6C/ Hardware Configuration Instructions - Serial Communication between Jetson Nano and PX4-6C flight controller.md](https://github.com/MShkut/JetsonNano-ROS2-PX4-Holybro-X500-V2/blob/3f28189c21d102e2add8f19fbc2d26098dbbd087/Serial%20Comms%20-%20Jetson%20Nano%20%26%20PX4-6C/%20Hardware%20Configuration%20Instructions%20-%20Serial%20Communication%20between%20Jetson%20Nano%20and%20PX4-6C%20flight%20controller.md)
    - Flight mode for control from companion computer
    - Data must be sent from external microcontroller via ROS2
    
    [Purdue ARC](https://www.notion.so/Purdue-ARC-0c464189c5454248a6cec8c4bf8c334e?pvs=21)
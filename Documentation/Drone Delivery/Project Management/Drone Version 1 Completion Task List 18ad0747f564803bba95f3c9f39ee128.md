# Drone Version 1 Completion Task List

### Navigation Stack in Simulation:

**Localization and Mapping:** 

- NECESSARY FOR END OF SEMESTER: Implement an algorithm that the odompublisher.cpp(in DD_Nav_WS/dd_gazebo_ws/drone_nav) can subscribe to for odometry messages - Also the algorithm needs to be visioned based
    
    There are 2 options:
    
    - ~~Implement Vi-SLAM(either Isaac-ros-ViSLAM or OrbSLAM) → publish nav_msgs/odometry and then the odompublisher.cpp will subscribe and use it for the drone odometry~~
    - Configure EKF2 PX4 algorithm → publish  px4_msgs/VehicleOdometry and then the odompublisher.cpp subscribes and then converts it to ROS coordinate frame and then uses it for the drone odometry([https://docs.px4.io/main/en/advanced_config/tuning_the_ecl_ekf.html](https://docs.px4.io/main/en/advanced_config/tuning_the_ecl_ekf.html))
    - Configure the PX4 VIO algorithm([https://docs.px4.io/main/en/computer_vision/visual_inertial_odometry.html](https://docs.px4.io/main/en/computer_vision/visual_inertial_odometry.html))
    - Or Use the Zed2i(our drone’s camera) SDK for global localization([https://www.stereolabs.com/docs/global-localization](https://www.stereolabs.com/docs/global-localization)) - COULD be very good
    - Look at which algorithm from PX4(VIO or EKF2 or Both??) would be the best option
    - Using VIO algorithm from the ROS2 Nav2 Library([https://docs.nav2.org/tutorials/docs/integrating_vio.html](https://docs.nav2.org/tutorials/docs/integrating_vio.html))
- GOOD BUT NOT NECESSARY: Implement a Lidar SLAM algorithm to create a 2d occupancy grid of the environment for the drone in mapping mode(seperate and before it begins autonomously navigating)
    
    Have members work on these simultaneously:
    
    - Implement ROS2 Lidar SLAM to create an accumulated point cloud of the environment(test the algorithm in the(or a) gazebo simulation) → could make it easier by having the LIO team adding a 3d lidar to the default nav2 world and with the default nav2 wheeled robot.
    - Create a Program to convert an accumulated point cloud to occupancy grid(see if the nav2 costmap2d can solve this problem: [http://mirror-ap.wiki.ros.org/costmap_2d.html](http://mirror-ap.wiki.ros.org/costmap_2d.html))
        - Figure out what type(s) of message the static map layer of the ros2 navigation2 costmap can take as input. The static layer of the costmap2d subscribes to the /map topic which is of type: nav_msgs/OccupancyGrid, so this needs to be what the point cloud is converted to(could try to search up point cloud to occupancy grid code to base off of).
        - Input:
            - Rosbag(load into Rviz):
                - https://drive.google.com/drive/folders/1CGYEJ9-wWjr8INyan6q1BZz_5VtGB-fP
            - Input msg type: [https://docs.ros2.org/foxy/api/sensor_msgs/msg/PointCloud2.html](https://docs.ros2.org/foxy/api/sensor_msgs/msg/PointCloud2.html)
        - Output:
            - Output msg type: [https://docs.ros.org/en/noetic/api/nav_msgs/html/msg/OccupancyGrid.html](https://docs.ros.org/en/noetic/api/nav_msgs/html/msg/OccupancyGrid.html)
        - Potential Starting Places:
            
            Videos to Watch:
            
            - [**ROS2 Occupancy Grid Node for Nav2**www.youtube.com › watch](https://www.youtube.com/watch?v=suqhnzIyq7w)
            - [**3D Pointcloud to 2D Occupancy Grid**www.youtube.com › watch](https://www.youtube.com/watch?v=8YC0zCV8kyM)
            - [**Getting Started with ROS2 and PCL: An Introduction to Point ...**www.youtube.com › watch](https://www.youtube.com/watch?v=VCobOzw2kHM)
            
            Repositories to look at: 
            
            - [https://github.com/jkk-research/pointcloud_to_grid](https://github.com/jkk-research/pointcloud_to_grid)
            - https://github.com/lidarmansiwon/occupancy_grid_map_generator
            
            Initial Steps: 
            
            - Create a ROS2 Workspace: https://www.youtube.com/watch?v=3GbrKQ7G2P0
            - Create a ROS2 python package: [https://www.youtube.com/watch?v=iBGZ8LEvkCY](https://www.youtube.com/watch?v=iBGZ8LEvkCY)
            
    
    **Core Navigation Stack:**
    
    - Finish debugging and testing script to call the NavigateToPose action client(Steven’s code), by publishing a gps point to the topic he subscribes to and then listening on the NavigateToPose action to see if action client request is sent
    - Test the full navigation stack(Just use the default nav2 rover and map to confirm all the nav2 parameters and behavior tree are created correctly) → Look into implementing waypoint follower mode
    - Test full navigation stack with drone in simulation(PX4-ROS2 code needs to be done/Millan needs to finish the takeoff, landing, and trajectory setpoint by then)
    
    **PX4 Code:**
    
    - Have Millan test his takeoff and landing code in the gazebo drone simulation with the proxmox VM
    - Have him write and test the trajectory setpoint code(either just through watching the topics in terminal, or in the simulation)
    
    ---
    
    ---
    
    ### Simulation → Real World
    
    - Set up Jetson(Set up ROS and all packages we need and the repo)
    - Configure the Zed2i(make sure can view its image data in ROS topics and that it is publishing to all the topics we need for the stack)
    - Convert any code reading from gazebo specific topics(not sure if there are any right now, but we just we need to confirm)
    - Set up video streaming to our front-end website
    - Set up code to allow communication over Wifi(most will be handled by the hardware team)
    - Do a Hardware In The Loop Test before doing our actual test on the IM field
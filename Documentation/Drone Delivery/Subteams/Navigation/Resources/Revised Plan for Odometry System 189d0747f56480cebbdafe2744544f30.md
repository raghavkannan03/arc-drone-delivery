# Revised Plan for Odometry System

We have three main requirements:

- Map environment to create a 2D map as the base - (NOT technically required for MVP)
    - Test a lidar slam function to create an accumulated point cloud
    - Create a program to convert the accumulated point cloud into a 2d occupancy grid
- Have VIO or Vi-SLAM algorithm that publishes odometry messages that can then be subscribed to by the odompublisher.cpp file - (Required for MVP)
    - Either use the EKF2 from PX4 or a Vi-SLAM algorithm(ORB-SLAM, isaac-ros-vi-slam)
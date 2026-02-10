# General Solution

Problem: We need a solution to land the drone so that users can access contents for delivery. 

Solution: To land a drone safely and precisely, use both visual fiduciaries and intelligent computer vision to determine safe ground.

Solution Breakdown: 

- Location detection solutions:
    - Apriltags: using these visual fiduciaries, we can detect the intended landing space and accurately compare the drone’s location to it.
    - GPS: using the general location of the drone, we go towards a general area for landing (allowing us to later scan the area for April tags.)
    - SLAM: Integrates acceleration data with GPS to produce a highly accurate location.
- Flat surface detection
    - Zed 2i’s depth mapping is initially used to determine whether area is safe to land.
    - 1D height sensors (IR) to find current height.
    - 360 turnaround to identify objects
        - Lightweight people detection
            - (check library)
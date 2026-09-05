# Adding OSM-based geospatial data to Gazebo

Author: ‣ 

OpenStreetMap is an open-source community-contributed source of geospatial data. It’s like Google Maps, but its data is free, not paid, to access.

1. Go to [openstreetmap.org/export](http://openstreetmap.org/export) and zoom in or select an area of data you would like to export.
2. Click Export on overpass turbo and export as .osm
3. Generate a gltf using the [OSM2World CLI](https://github.com/tordanik/OSM2World/tree/master/src/main/java/org/osm2world/console) with the small-campus.osm file
    1. Open any IDE (Intellij) and Add new Configuration 
    2. Under Configuration, Add a new Application and set Main Class to OSM2World class (under /src/main/java/org.osm2world/console)
    3. After applying the configuration, running the program should print a list of flags that the program supports
    4. Edit the program argument field into the configuration made previously 
    5. (Note: if using the input and output flag, use absolute path of the osm file as input and output)
4. Open Blender
5. File > Import the gltf
6. Remove the default starting cube, light, and camera, and collection
7. File > Export as COLLADA (.dae) to a new folder
8. Create a new gazebo world file in that new folder as described here
[https://classic.gazebosim.org/tutorials?tut=import_mesh&cat=build_robot](https://classic.gazebosim.org/tutorials?tut=import_mesh&cat=build_robot)
and modify the path to the .dae file to be the one you saved it as

12. Run

```
gazebo my_mesh.world
```

and it should start with the world

![Untitled](Adding%20OSM-based%20geospatial%20data%20to%20Gazebo/Untitled.png)
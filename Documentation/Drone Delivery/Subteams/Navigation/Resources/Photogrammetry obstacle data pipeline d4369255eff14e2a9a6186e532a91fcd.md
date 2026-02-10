# Photogrammetry obstacle data pipeline

In Spring 2023, Seth used his 360 camera to capture a sequence of 360 images that were then converted into 3D photogrammetry models using OpenDroneMap.

The thought was that we could later utilize our camera on our drone to create capture a series of images and generate a 3D model of the operational environment to then be store long-term obstacle data and update it every-so-often. The 3D model would also be used by [App Development](../../App%20Development%208f1d32df9bc14ccda840af9e4516cf62.md) in the operations app to see where the drones are in the world.

The 360 camera implementation was just a fun one, but it resulted in this script being produced:

[GitHub - lectrician1/Insta360-2-ODM: PowerShell script to convert a GPS-tracked video recorded on an Insta360 camera into a GPS-tagged image sequence](https://github.com/lectrician1/Insta360-2-ODM)
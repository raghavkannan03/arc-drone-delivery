# App Development

Developing a drone delivery operations web app and maybe a mobile Flutter app for making orders in the future.

We’re building this to replace QGroundControl so that we can actually operate multiple drones at once and download data to them without having a constant connection.

# Links

[Why we chose stuff](App%20Development/Why%20we%20chose%20stuff%20c755f50b60bf4267b70a402ddea895c1.md)

Repository: [https://github.com/purdue-arc/drone-delivery-website](https://github.com/purdue-arc/drone-delivery-website)

Vaultwarden (where keys are stored): [https://vaultwarden.purduearc.com](https://vaultwarden.purduearc.com)

[Database schema draft](App%20Development/Database%20schema%20draft%20ba4da3299ac6479fa826cc8e14c2a357.md)

Stale mobile app repository (just flutter demo): [https://github.com/purdue-arc/dd_mobile_app](https://github.com/purdue-arc/dd_mobile_app)

[Running OpenDroneMap](App%20Development/Running%20OpenDroneMap%206d62fee131cc4ca9b64e789d151fbb4f.md)

Cesium tile store database for storing photogrammetery used by cesium: [https://github.com/3DGISKing/CesiumJs3DTileServer](https://github.com/3DGISKing/CesiumJs3DTileServer)

Media Server for VIdeo Streaming

https://github.com/bluenviron/mediamtx

# Features

- Drone delivery management dashboard
    - Weather details
    - Drone usage analytics
    - Drone list
    - 2D map of drone locations
- Simple delivery maker
    - Select drone
    - Select destination
    - Load package
    - Send off
- Flight planner/viewer
    - 3D map editor
        - Shows
            - Objects: Buildings and trees
            - Terrain
            - Satellite imagery
            - Photogrammetry
            - Legally restricted flight zones
            - Weather
        - Allows user to edit flight path
            - Start
            - Destination
            - Waypoints
                - Altitude
                - Speed
    - 2D flight progression editor:
        - Shows timeline of altitude and speed
        - Curves in paths. Beizer curve editor that can be used to make curves in the flight path, altitude, and speed progression.
    - Flight planner parameter editor
        - Altitude range: Altitude range the drone should stay in during its cruising.
        - Speed range: Speed range the drone should stay in for the entire flight.
        - Landing battery percentage: Flight range should be limited to range that is possible with this percentage of battery left.
        - Package weight
        - Drone weight
        - Takeoff time: Planned time of takeoff to account for closed airspace or weather if planning for a future flight time.
        - Confidence level: Plans should only be created that have a calculated probability of completion greater than the confidence level.
    - User flight planning options:
        - Manual: A user should be able to plot waypoints for the drone to follow.
        - Automated: A computer should be able plan a path given a start and destination and waypoints they must pass through. An entire flight or just specific parts or a manuall-planned flight can be automatically. Users can edit automatically-planned flights.
    - Planning constraints:
        - Legal: The plan must only be in legal airspace for drones to fly in.
        - Obstacle-free. Avoids all:
            - Objects
            - Other drones
        - Optimized: Every planned flight must optimize these variables. We will need to experiment balancing them to establish a system that delivers all 3 in the best way possible.
            - Speed: The package should be delivered as fast as possible.
            - Energy efficiency: Energy usage should be minimized so that we can travel the farthest distance and use the least amount of power.
            - Safety: The router should account for the probability of encountering unknown obstacles or weather based on the known preflight environment. For example, if the flight path is through an area of trees that have unknown size, the planner should should consider the area to have a high probability for encountering obstacles and account for that in the possible flight time.
    - Editable live: The flight plan should be able to changed in the air.

# Nhost tips

- Always create a table with an autoincrementing column in Hasura instead of Nhost or using another schema. Hasura uses Postgres sequences to track autoincrementing values whereas Nhost uses identities. Hasura will not autoincrement with identities if you try to run a mutation with providing no value for an autoincrementing column.
# Related drone companies/designs

# Zipline

- Delivering with plane drones (Platform 1) in Rawanda using parachute system. Uses launcher and parachute to release and catch the drone.
- Testing delivery in the United States using their Pentacopter/winch system (Platform 2) happening in Pea Ridge, Arkansas. It’s mostly just an R&D facility that’s attached to a very small walmart. Pea Ridge is a very small town. Platform 2 has rotating propellers that can switch from vertical to horizontal flight.
- Can see diff between Platform 1 and 2 here: https://www.flyzipline.com/about/zipline-fact-sheet. Highlights for platform 2 include:
    - 8 pound payload
    - 10 miles service radius, or 24 miles one way
    - Cruise speed 70 miles per hour
- There seem to be no flight advisories in Pea Ridge on Airhub, so I think the autonomous technology can detect drones on its own
- Has system figuring out with FAA to clear an airspace path that drone deliveries will be made in
- Navigation stack
    - Does 2.5D path planning (uses raster map with colors to represent heuristic values)
    - Has to plan the entire flight (forward and vertical flight before the drone launches instead of doing it onboard. Needs to do it very quickly. Needs to manage risk, not fly over risky areas. Does this ahead of time to get most efficient flight, not spending too much time in vertical flight.
    - Manage weather
    - Has like 400ft turning radius in forward flight, plans curves ahead of time.

# Flytrex

[https://www.flytrex.com/](https://www.flytrex.com/)

- Small US startup delivering in Texas and North Carolina that’s actively doing deliveries. They have a weird system of picking up deliveries by bike and then bringing them to dist hub to be sent by drone.
- Drones are simple hexacopter platform with multiple batteries on the side between the arms of the drone. Large box below
    - 5 miles roundtrip
    - 32 mph
    - Completely autonomous
    - They seem to have a radar on them to avoid other drones?
    - There is a Drone NOTAM in granville

# UPS

UPS Flight forward is the name of the operation. Literally released a truck that had a drone on it a few years ago but no updates since.

# DJI

- Has signature delivery drone for non-autonomous operations, the Flycart 30
- [https://www.youtube.com/watch?v=Hhp11I-vGHA](https://www.youtube.com/watch?v=Hhp11I-vGHA)
- Has winch and package box delivery systems
- Stats:
    - 4m diameter
    - 2 batteries (can remove one for greater capacity
    - 30 min hovering time
    - 28 km flight distance
    - 20 m/s
    - 8 motors
    - 30 kg payload
    - 38000 mAh batter. 1984 Wh
- Has DJI DeliveryHub software to manage drones (like our DD website)

# Wing

- Google subsidiary
- Delivering with Walmart in Texas
- Various sized drones with multple small propellers. Smaller props mean less noise
- No package container. Custom delivery pouch that is dropped by winch

![image.png](Related%20drone%20companies%20designs/image.png)

# Matternet

[https://www.matternet.com](https://www.matternet.com/)

- Palo Alto company doing deliveries in palo alto.
- Quadcopter with winch

# Wingcopter

- German company doing deliveries aroudn world in small settings
- Drone features
    - Small props
    - Wing-based drone with vertical props
    - Winch. Carries multiple packages

# Manna

- Ireland
- https://www.manna.aero/
- Winch
- 8 motos, doubled up

# Others

- [Elroy air](https://elroyair.com): Massive cargo drones. Britain.
- DroneUp: Consulting company for private autonomous drone delivery operations
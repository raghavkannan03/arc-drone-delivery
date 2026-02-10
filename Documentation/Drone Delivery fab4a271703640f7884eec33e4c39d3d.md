# Drone Delivery

Welcome to the Drone Delivery project! We’re making Starship but with drones!

Imagine a system of thousands of drones, autonomously navigating obstacles, receiving and dropping off packages with *zero* human intervention. That is a **massive** project currently being taken on by companies like Amazon, UPS, and Zipline. We’re looking to do that here at Purdue as ARC!

# Project Overview

An overview of the goals of this project:

- Determining the path the drone both before and during the flight by using:
    - Geospatial data
    - Path finding algorithms
    - Inter-drone communication
    - Weather data
    - Obstacle detection & avoidance
- Building and designing a drone and drone storage system that:
    - Can carry a meal or small package
    - Withstand collisions and light weather
    - Fly 20 minutes
- Developing backend server and software infrastructure that is:
    - Scalable & Realtime
- Developing fronted software to:
    - Control the drone
    - Manage the delivery operations of hundreds of drones
    - Order deliveries

# Minimal Viable Product (MVP)

- Drone that can carry a 1-2 kg package from one end of the IM fields to the other and navigate around known and unknown obstacles
- Evaluation:
    - User loads package on the drone
    - User initiate an order/flight from the website
    - Backend determines a non-linear flight path/plan that avoids obstacles (can be imaginary) and sends this to drone
    - Drone takes flight
    - Drone detects an unknown obstacle like a stadium light post and successfuly navigates around it.
    - Drone releases package at delivery point (can be winch or landing)
    - Drone returns to starting point

# Goals/Timeline

## Spring 2025

Hardware

- submit general part requests for v2
- test flight v1
- finish building v1. we're barely able to get stuff ordered now so right now so doubtful...
- design v2 (maybe not finish design)

Navigation

- simulate drone
- write onboard sw to read from db and issue mav signals to drone

Website

- Write sw to stream video to website.
- test streaming in flight
    - setup recording server to save video

TOGETHER: fly drone autonomous WITHOUT obstacle avoidance (just set waypoints)

## Fall 2025

Hardware

- Finish v2 design by end of sem
- Start order, build, flight, of v2

Software

- work on obstacle avoidance, begin testing when ready

## Spring 2026

- finish v2 build, fly v2 with full sw stack

## Useful Pages

[Project Management](Drone%20Delivery/Project%20Management%20ca3054da62714a6fbf0ed9418448c266.md)

[Subteams](Drone%20Delivery/Subteams%20926f90d2ad9d4c2fa26cc724d2df396a.md)

[Related drone companies/designs](Drone%20Delivery/Related%20drone%20companies%20designs%202cca88c327d941879ebc7ffbfd888ad6.md)
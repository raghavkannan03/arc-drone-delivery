# BEFORE YOU FLY

Before you ever fly one of our drones, you MUST read this document. It describes the various safety and legal aspects of flying drones.

# Flying the drones

FLYING AERIAL OBJECTS CAN BE AN EXTREMELY RISKY AND LIABLE ACTIVITY.

## Risks

### Legal

The FAA nationally regulates all space above the ground and as soon as you lift off, you are now in the national airspace and subject to following all regulations as well as being prone to running into any other air traffic which may come from any other direction at any time. This includes other drones as well as controlled (IFR) and uncontrolled manned aircraft (VFR) which could be operating below 400 feet.

It is extremely important to follow all aerial regulations as drone flight is an extremely visible public activity that is extremely prone to police questioning and thus getting you into possibly fines, suspensions, or prison with Purdue, State, and Federal law. 

When interacting with police, just provide your ID, TRUST and drone registration certificates, and state that you have permission to operate on Purdue property as a student of Purdue doing drone flight for research purposes. You must do the first part to fulfill Indiana law and the second to demonstrate you have permission to be on Purdue property. Purdue Police enforce both Indiana law and Purdue policies so you must fulfill both.

Do not answer any questions like if you have LAANC approval and just say “I respectfully would like to not answer any questions at this time under my 5th amendment rights”. You can even ask the officer if you are required to answer questions if you are unsure. They will respond truthfully. Police questioning will feel very pressuring as they will like you are in big trouble and you may feel like you need to say the truth and state what you have done. Don’t. You can possibly incriminate yourself and admit fault which could be used against you in the future.  If you refuse to answer questions, they will contact their supervisors on the spot and verify that you have permission to fly. This can take a long time. You just have to wait through it. Your interaction with police will all be documented in a police report. Police if they’d like (ALWAYS assume they will) can later contact the FAA and report any suspected infraction, even if they let you off with a warning. This is also why it is extremely important to not admit fault as it can literally be used against you if you later are in trouble with the FAA.

If they ask if you got permission to fly, ignore it. They can find that out on their own. They might not even know the regulations themselves about flying drones. Police ARE ALLOWED TO LIE. They can accuse you of doing something that you might not have and they don’t even know that you did it or not. Ignore it.

### Physical

Drones can:

- Fall out of the sky and become extremely forceful objects that with enough height and/or weight can seriously injure or kill people. That is why it is important to never fly over or in the proximity of people.
- Become out of control and slam into people or property, causing you to not only be responsible for the damage costs of the drone, but also the damage costs of whatever property or person you damaged.

As you can tell, ground-based objects do not have these risks. Moving from 2D to 3D space has a lot more consequences.

## Causes of risk

Potential causes of this can include:

- Structural failure of the drone frame or propellers.
- Damage to the drone’s components from an outside source like an obstacle, a bird, or hostile person.
    - Shot at
    - GPS jamming
    - EMF interference
    - Nets
    - Kamikaze drones
- Sudden electronics failure (flight controller computer, flight controller sensors, ESCs, GPS module, motors).
- Disconnection of drone components from each other or the frame (signal wires to flight controller comes undone, motors unscrew from frame, propellers detach from motors).
- Disconnection from the drone RC controller or GPS signal.
- Over current
- Battery failure if out of voltage. Different conditions may cause the battery to drain faster such as colder weather or a larger load.
- Weather conditions including high wind, sudden gusts, rain, snow.

I would encourage you to look up videos like “drone failure” or “drone falling” to see what kind of failures people have encountered and the consequences.

## Mitigating risk

Some of these are specific to the new drone.

Make sure with reliable testing prior to frequently flying:

- The battery’s true voltage matches what is shown in QGroundControl.
- Test maximum operating conditions including:
    - Max current drawn when loaded and flying.
    - Max/min operating temperature and flight time.

Make sure before **every flight.** **USE THIS AS A CHECKLIST**

- Make sure the drone’s frame and propellers are locked-in and with no signs of damage.
- Make sure ALL drone components and wires are shielded, and securely strapped, taped, or screwed in. A physical cover should be in place to protect the drone’s components on the top from falling off or being attacked by birds.
- All connectors are locked or extremely resistive to becoming undone. Avoid connectors like USB for electronic components which are prone to becoming disconnected.
- Proper failsafes are in place and that such failsafes will not cause additional failures. For example, if the drone’s response to extremely low battery voltage is to land where it is, make sure it will not be in a situation where it will land on a tree or other unstable object. Or, that might not be possible, so make sure when the drone is at a low voltage, it has enough to get home and away from obstacles.
- Have drone registration and TRUST certificates on-hand.
- Have permission to pilot a drone from the property you are on. You can legally fly a drone above any private property (that is not an exception like nationally sensitive areas like power plants, railroads, etc.) as it is part of national airspace, however you DO NOT have permission to launch a drone from private property as you are on the ground and thus subject to the property owner’s permission.

**If you are flying from Purdue property**, per Dave Truett (Senior Risk Analyst for Purdue), “We allow for operation on campus for educational and research purposes for our faculty, staff, and students.  If you are operating under a PU recognized club you would fall under this blanket approval.”
- Have checked current airspace restrictions by going to [https://air.aloft.ai](https://air.aloft.ai/) and getting LAANC approval if necessary. You must do this even if you know you are not flying in LAANC-required airspace as there can be temporary airspace restrictions in place where you are flying.
- If you applied for LAANC, constrain the drone’s operation to the LAANC operating area if necessary.
- Checked the weather. Do not fly in high wind, rain, snow, drizzle. This is because:
    - The motors are apparently water resistant
    - The ESCs have no indication of being water resistant (hobbywing does sell professional level ESCs that are water resistant, but ours are not the professional level type).
    - The flight controller is not water resistant. If water gets between a power and ground pin on the flight controller, it could cause damage to it. That’s why it needs to be covered.
    - If you want make resistant to water in the future, read this: [https://dronevibes.com/forums/threads/how-to-build-a-water-resistant-multirotor-including-barometer.31185/#google_vignette](https://dronevibes.com/forums/threads/how-to-build-a-water-resistant-multirotor-including-barometer.31185/#google_vignette)

Make sure during every flight: **USE THIS AS A CHECKLIST**

- ALWAYS fly with a friend by your side. They will reduce your chances of making mistakes significantly and will be able to monitor drone telemetry and the space around the drone while your eyes are on the drone.
- Fly with utmost caution and in an open area so you can connect to GPS and you can avoid running into tall obstacles like trees, lightposts, and buildings. This is a $2700 drone. Trees are the #1 THREAT TO DRONES. Flying a vehicle from a 3rd person view makes it difficult to judge the drone’s proximity to other objects from a distance. Trees are particularly difficult because the position of branches are difficult to judge compared to solid objects. Keep your distance from obstacles. Do not fly a drone at high speeds.
- Connect to QGroundControl to monitor the battery voltage while you fly. The controller (currently) does not show the voltage from the drone. There is automatic return to home if the battery voltage is low, but you should not rely on that. Also it’s always good to see diagnostics in realtime, especially if anything goes wrong in flight you can possibly evaluate after.
- Monitor your area of operation so that no people enter it.
- Maintain visual line of sight.
- Stay in your authorized LAANC area and altitude limit.
- Monitor the battery’s voltage while you are flying.
- Maintain signal communication.
- Be ready to flip the kill switch.

Notes:

- The chance that the flight controller fails is likely extremely low. However before ever deploying a production system or applying for flight over people, it would be good to test the longevity of such components by operating in a safe environment for a long period to demonstrate its reliability. Kind of like what Walmart/UPS have done by doing test remote deliveries first before ever deploying them in an urban environment. Dual flight controllers are also a thing but honestly with enough testing showing no possible failure, this might not be necessary.
- We were looking at making a parachute, however note that a parachute won’t help in all cases (if lands on tree, building, and falls further, or too low). Also, we need to consider whether we want parachute’s deployment to be connected to the flight controller or a separate system. The flight controller is very unlikely to fail so a separate system might now make sense. The flight controller could fail if the battery runs out, fails, or it’s struck by lightning, becomes disconnected, etc. If we do decide on a separate system we need to evaluate how separate. Will it have its own battery? if so, how will it be recharged? We’ll need to design and manufacture it then. Look into flight over people authorizations for large drones and see how they got approval.
- The operation of our drone has liability insurance under that we are a Purdue club per Dave Truett. If our drone damages property or people, we will be covered. 

It also has property damage coverage, given that it was funded by Purdue (and is thus owned by Purdue). The coverage is a $1000 deductible and covers theft and damage to the drone that took place when it was not flying. David Truett (risk management Purdue) made this clear to Seth.
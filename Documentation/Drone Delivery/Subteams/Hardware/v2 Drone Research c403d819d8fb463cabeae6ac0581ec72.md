# v2 Drone Research

Goal: A production-level-drone in terms of mechanical hardware, but not actual design. aka nothing is sealed, can't fly in percipitationweather conditions, not resistant to tampering). Test with large amount of flight time, various wind conditions, etc. Understand operation characteristics.

Thoughts:

frame with larger base
use power delivery board sitting in box downstairs
6 new motors
another battery (design recharge / swap system?) (will need 2 then)
make parachute/airbag system design
another flight controller
smaller camera then zed, maybe use our own camera sensors? camera sensors 360 degrees around drone? integrate solid state lidar if needed? This might be hard to budget/design for for v2. maybe make a v2.5 that just has upgraded sensors.

# Frame

- Looks like for the hexacopter frames tarot offers, if you want to go over 1m in diameter, you need to get an octacopter frame
- the T960 frame we have rn is the widest hexacopter frame they make ($300)
    - Looks like people strapped multiple batteries to the legs: [https://www.youtube.com/watch?v=Avvx9J2y7RU](https://www.youtube.com/watch?v=Avvx9J2y7RU)
    - Or put large landing legs and then camera below battery: [https://www.youtube.com/watch?v=Orq9uVMF6aQ](https://www.youtube.com/watch?v=Orq9uVMF6aQ)
- > 1 m frames (octacopters)
    - Models
        - T18: 1.2m $500
        - T15 1m $500
    - Notes:
        - Bases don’t look much larger than what we have

Props $20 * 3

[Large T960 Tarot foldable landing gear](https://www.ebay.com/itm/305786229848) $60

We’ll just go with T960 again and use space efficiently

Housing: $10 

Stabilization for electronics: $90

Total: $500

# Motors/ESCS

We want professional motors/escs for diagnostics and failover if a motor fails

Hobbywing

- [H6M system](https://www.hobbywingdirect.com/collections/uav-system/products/xrotor-h6m?variant=40960896893043) $215

T Motor

- [Integrated](https://store.tmotor.com/categorys/uav-integrated-propulsion-system) $200

These all require 12s, 14s, 16s, systems

250 * 6 = $1500

# Other drone avoidance?

Maybe want. the other companies have it.

ChatGPT recommends Echodyne's EchoFlight. That’s a contact us though. Prob very expensive 5k+

Prob want to avoid for now.

Maybe could make diy FMCW radar, software defined radar.

# Parachute system

We are making our own. [https://chatgpt.com/share/679e5aa3-cf18-8011-a6af-d7a28cd55db8](https://chatgpt.com/share/679e5aa3-cf18-8011-a6af-d7a28cd55db8)

- [Parachute](https://shop.fruitychutes.com/products/iris-ultra-72-standard-parachute-28lbs-20fps?variant=31640928845914&country=US&currency=USD&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&gad_source=1&gclid=CjwKCAiAqfe8BhBwEiwAsne6gaGB2AdiJemYlRlWVC7CbDdqWRngR_XTGchAoTEyHlfvVn7I556hehoC7L8QAvD_BwE) $300
- **CO₂ Cartridge Ejection** ($150) – Fast, powerful deployment
- **Electronics & Sensors** ($100)
    - **Microcontroller (ESP32, Arduino, or similar)** ($10–$40)
    - **Barometer/Altimeter (BMP280 or similar)** ($10–$30) – Detects altitude loss
    - **IMU (MPU6050 or similar)** ($10–$30) – Detects sudden free-fall
    - **Servo or Solenoid for Triggering Ejection** ($15–$50)
- Battery $20
- Housing $10

Total: $600

inspiration: [https://manta-air.com](https://manta-air.com/)

# Electronics

May make a custom board to combine jetson and flight controller.

Flight controller (maybe one with more ports like 6X?): $300

Orin Nano super dev board (or module, cheaper): $250

GPS M10: $50

WiFi Halow for connectivity: $250

Wires, connectors: $100

- Ones for flight controller/pcb
- Battery connectors

Camera $500

- zed 2i again
- 2, 3 gopros or other wide angle action for 360 vision

Servos for winch system $50

Remote ID

Storage $25

Total: $1500

# Battery

2x 10000mAh = $500

DIY battery swap ssytem. Dude chatgpt estimate is coming around $2k for a low end system. also we’re going to need acctuators and stuff. does not seem fun to design. If the drone could carry batteries like packages that would be pretty cool. Later [https://chatgpt.com/share/679e5ab6-1200-8011-9579-74667cc6aaf0](https://chatgpt.com/share/679e5ab6-1200-8011-9579-74667cc6aaf0)

# Total

$4600

v1

Wifi
# Arduino-Robot-Journey-Complete-Learning-Portfolio
This repository documents my journey in building my first autonomous Arduino line following robot with obstacle detecting abilities starting with 6 foundational experiments consisting of smart distance alert, IR line detection, motor control, obstacle avoidance logic, line-follower algorithm, and serial communication to the final autonomous robot.

Timeline : December 2025 - January 2026
Status : In-progress

Technical Specifications :
1. Microcontroller : Arduino Uno R3 (ATmega328P)
2. Sensors : HC-SR04 Ultrasonic (2-400 cm range), Obstacle Avoidance IR sensor, TCRT5000 IR Reflective Sensors
3. Motor5 Control : L298N Dual H-Bridge Driver
4. Actuators : 2 yellow TT geared DC motors (200-300 RPM)
5. Power System : 7.4V Battery + Voltage Regulator LM2596 (Buck Converter DC-DC Step Down Module )
6. Chassis : Custom acrylic frame

Software Stack :
Platform : Arduinjo IDE 2.0+
Language : Embedded C++ (Arduino Framework)
Communication : Serial UART @ 9600 baud

Progressive Learning Experiments :
1. Smart Distance Alert System : Detecting the distance of an object from the HC-SR04 ultrasonic sensor causing different colour LEDs to glow depending on the distance. Red : For distance < 10 cm (Danger Zone), Yellow : For distance 10-30 cm (Caution Required), Green : For distance > 30 cm (Safe Zone)
2. IR Line Detection Logic : Using 3 Obstacle Avoidance IR sensors to detect the presence of line by the right, center and left IR sensors respectively.
3. Motor Control System : Controlling the speed and direction of rotation of wheels using PWM signals.
4. Obstacle Avoidance Logic : Controlling motion and direction of wheels based on obstacle detection (forward movement incase of no obstacle is detected, stop motion incase obstacle is detected, reverse and then move again).
5. Line-Follower Logic System : Moving forward if line is detected by right IR sensor, 
6. Serial Control Protocol :

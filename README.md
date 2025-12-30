# Arduino-Robot-Journey-Complete-Learning-Portfolio
This repository documents my journey in building my first autonomous Arduino line following robot with obstacle detecting abilities starting with 6 foundational experiments consisting of smart distance alert, IR line detection, motor control, obstacle avoidance logic, line-follower algorithm, and serial communication to the final autonomous robot.

**Timeline :** December 2025 - January 2026

**Status :** In-progress


**Technical Specifications :**

*1. Microcontroller :* Arduino Uno R3 (ATmega328P)

*2. Sensors :* HC-SR04 Ultrasonic (2-400 cm range), Obstacle Avoidance IR sensor, TCRT5000 IR Reflective Sensors

*3. Motor Control :* L298N Dual H-Bridge Driver

*4. Actuators :* 2 yellow TT geared DC motors (200-300 RPM)

*5. Power System :* 7.4V Battery + Voltage Regulator LM2596 (Buck Converter DC-DC Step Down Module )

*6. Chassis :* Custom acrylic frame


**Software Stack :**

*Platform :* Arduino IDE 2.0+

*Language :* Embedded C++ (Arduino Framework)

*Communication :* Serial UART @ 9600 baud


**Progressive Learning Experiments :**

*1. Smart Distance Alert System :* Detecting the distance of an object from the HC-SR04 ultrasonic sensor causing different colour LEDs to glow depending on the distance. Red : For distance < 10 cm (Danger Zone), Yellow : For distance 10-30 cm (Caution Required), Green : For distance > 30 cm (Safe Zone).

*2. IR Line Detection Logic :* Using 3 Obstacle Avoidance IR sensors to detect the presence of line by the right, center and left IR sensors respectively.

*3. Motor Control System :* Controlling the speed and direction of rotation of wheels using PWM signals.

*4. Obstacle Avoidance Logic :* Controlling motion and direction of wheels based on obstacle detection (forward movement incase of no obstacle is detected, stop motion incase obstacle is detected, reverse and then move again).

*5. Line-Follower Logic System :* Controlling the direction of movement of wheels based on line detection by 3 IR sensors (moving towards right direction if line is detected by right IR sensor, moving towards left direction if line is detected by left IR sensor, moving forward if line is detected by center IR sensor).

*6. Serial Control Protocol :* Controlling the direction of movement and speed of the wheels based on commands given to the serial monitor.   


**Skills Demonstrated :**

*1. Embedded Programming :* Using C++ Arduino programming to perform the experiments as well as operate the final robot.

*2. Control Systems :* Implementing the line-following and obstacle-detecting logic in the robot.

*3. System Integration :* Integrating HC-SR04 Ultrasonic sensor as well as the TCRT5000 IR Reflectance sensors to build the final autonomous robot.

*4. Testing and Validation :* Performing extensive testing and failure analysis to make the robot work.

*5. Technical Documentation :* Building the comprehensive GitHub repository with the required schematics, code and explanations.


**Challenges and Solutions :**

While building our first autonomous robot, we faced the following issues.

*1. Motor not moving / moving too slow :* Reasons for such issues maybe insufficient power supply or incorrect wiring to the L298N. This problem could be fixed by checking the power supply and the L298N connections.

*2. Wire Tangling / Connection Issues :* This could occur due to unstable breadboard connections, vibration during movement or poor cable connections. This could be solved by ensuring firm connections by using jumper wikres with strong connectors and using hot glue for critical connections.

*3. False readings by ultrasonic sensor/ IR inconsistent line detection :* This problem could arise due to noise interferance. The problem could be solved by checking and modifying the code.

*4. Sensor Placement Conflicts :* The IR and Ultrasonic sensors may interfere with each other. This problem could be solved by placing the sensors at proper positions while keeping appropriate distance between the sensors.

*5. Code Errors :* The errors in code could be solved by checking the structures of the code, defining proper delays and making necessary changes in the code so it can be debugged and executed easily.


**Conclusion :**

This comprehensive robotics journey helped us build our first autonomous Arduino robot by successfully tranforming our theoretical knowledge into technical expertise through six progressive experiments culminating in a fully functional autonomous line follower robot with obstacle detection ability. This systematic approach from indivisual component testing, to a fully intgegrated system demonstrates not just technical competency, but also critical engineering mindset.

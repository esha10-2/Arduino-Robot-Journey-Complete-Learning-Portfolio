# Learning Notes - Experiment 03: Motor Control

## What I Learned

### 1. H-Bridge Fundamentals
- Four switches control motor direction
- PWM controls speed (0-255 = 0-100% duty cycle)
- Never turn on diagonal switches simultaneously (shoot-through)

### 2. L298N Driver Module
- Dual H-bridge controls 2 motors
- Requires separate logic (5V) and motor (7-12V) power
- Heatsink essential for continuous operation
- Enable pins for PWM speed control

### 3. Practical Applications
- Robot locomotion (forward/backward/turn)
- Speed control for precision movement
- Braking and coasting modes

## Key Insights
- Motors draw 3-5x more current when starting (stall current)
- Back EMF can damage circuits without flyback diodes
- Separate power supplies prevent Arduino reset
- Motor calibration needed for straight movement

## Skills Developed
- Power electronics basics
- PWM implementation
- Multi-voltage system design
- Motor protection circuits
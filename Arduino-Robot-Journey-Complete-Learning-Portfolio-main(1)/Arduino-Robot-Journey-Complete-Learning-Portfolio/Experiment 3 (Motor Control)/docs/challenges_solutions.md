# Challenges & Solutions - Experiment 03

## Challenge 1: Motor Doesn't Move
**Problem:** Motors hum but don't rotate at low PWM
**Solution:** Minimum PWM value needed (typically 30-40)

## Challenge 2: Arduino Resets When Motors Start
**Problem:** Voltage drop on 5V rail
**Solution:** Use separate power supplies for Arduino and motors

## Challenge 3: L298N Overheats
**Problem:** Driver gets too hot quickly
**Solution:** Add heatsink, reduce PWM frequency, ensure good airflow

## Challenge 4: Motors Run at Different Speeds
**Problem:** Same PWM gives different speeds
**Solution:** Individual calibration for each motor

## Challenge 5: Electrical Noise
**Problem:** Sensor interference when motors run
**Solution:** Separate wiring, add capacitors, use twisted pairs
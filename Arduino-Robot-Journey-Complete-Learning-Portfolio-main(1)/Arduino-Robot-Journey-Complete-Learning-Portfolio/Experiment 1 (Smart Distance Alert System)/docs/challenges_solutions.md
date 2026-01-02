# Challenges & Solutions

## Challenge 1: Inconsistent Distance Readings
**Problem:** Sensor gave different values for same distance
**Solution:** Added averaging - take 5 readings, use average
**Code fix:** Created `getAverageDistance()` function

## Challenge 2: LEDs Too Bright/Dim
**Problem:** Different LED colors had different brightness
**Solution:** Used 220Ω resistors for all LEDs
**Reason:** Safer current, longer LED life

## Challenge 3: Serial Monitor Freezing
**Problem:** Stopped showing data after few minutes
**Solution:** Reduced print frequency, added small delays
**Tip:** Don't print in every loop iteration

## Challenge 4: Wiring Confusion
**Problem:** Forgot which wire goes where
**Solution:** Used color coding:
- Red = Power (5V)
- Black = Ground (GND)
- Green = Signal to Arduino
- Yellow = Signal from sensor

## Lessons Learned
1. Test each component separately first
2. Take photos before disassembling
3. Comment code as you write it
4. Keep wiring tidy from start
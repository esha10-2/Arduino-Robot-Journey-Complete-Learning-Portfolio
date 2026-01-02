# Challenges & Solutions - Experiment 02

## Challenge 1: Inconsistent Line Detection
**Problem:** Same line gave different readings at different times
**Symptoms:** 
- Robot sometimes detects, sometimes misses
- Readings change with lighting conditions
- Sensor height affecting detection

**Root Cause:**
- **Ambient light interference**: Room lights/ sunlight affect IR sensor
- **Sensor height variation**: Not maintaining constant distance
- **Surface reflectivity changes**: Dust/dirt on surface

**Solutions:**
1. **Added black tubing** around sensor to block ambient light → ✅ 80% improvement
2. **Fixed sensor height** at 5mm from surface → ✅ Consistent readings
3. **Implemented auto-calibration** on startup → ✅ Adapts to surface
4. **Added averaging filter** (10 samples) → ✅ Smooth readings

## Challenge 2: Sensor Calibration Complexity
**Problem:** Need to recalibrate for every surface
**User unfriendly**: Hard to adjust for beginners

**Solutions:**
1. **Created calibration routine** in setup():
   ```arduino
   void calibrateSensor() {
     Serial.println("Place on WHITE surface...");
     delay(3000);
     whiteValue = analogRead(IR_PIN);
     
     Serial.println("Place on BLACK line...");
     delay(3000);
     blackValue = analogRead(IR_PIN);
     
     threshold = (whiteValue + blackValue) / 2;
   }
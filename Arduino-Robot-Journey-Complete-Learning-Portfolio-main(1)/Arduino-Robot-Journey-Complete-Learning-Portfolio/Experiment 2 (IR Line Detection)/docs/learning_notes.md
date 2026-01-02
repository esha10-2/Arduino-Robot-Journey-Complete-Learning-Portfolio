# Learning Notes - Experiment 02: IR Line Detection

## What I Learned

### 1. Infrared Reflection Principle
- TCRT5000 emits **infrared light** and detects reflection
- **Black surfaces** absorb IR → low reflection → high sensor output
- **White surfaces** reflect IR → high reflection → low sensor output
- **Analog vs Digital**: TCRT5000 gives analog values, converted to digital

### 2. Sensor Calibration
- Every surface has different reflectivity
- Must **calibrate for each surface** (floor, table, track)
- **Dynamic thresholding**: Can adjust sensitivity in code
- **Ambient light interference**: Sunlight affects readings

### 3. Edge Detection Logic
- **Single sensor**: Can detect black/white transition
- **Sensor array**: Multiple sensors for line position
- **Decision logic**: Left/center/right detection for navigation

### 4. Practical Applications
- **Line-following robots**: Industrial AGVs, educational robots
- **Object detection**: Conveyor belt sorting
- **Position sensing**: Print head alignment

## Skills Developed
1. **Analog sensor interfacing** (analogRead())
2. **Threshold calibration** for different surfaces
3. **Noise filtering** for stable readings
4. **Multi-sensor array** management

## Technical Insights
- **IR wavelength**: 950nm (invisible to human eye)
- **Detection range**: 0-2cm optimal
- **Response time**: < 10ms
- **Current consumption**: ~20mA

## Real-World Relevance
- Factory automation (line following AGVs)
- Print media alignment
- Automotive lane detection (simplified)
- Robotics competitions
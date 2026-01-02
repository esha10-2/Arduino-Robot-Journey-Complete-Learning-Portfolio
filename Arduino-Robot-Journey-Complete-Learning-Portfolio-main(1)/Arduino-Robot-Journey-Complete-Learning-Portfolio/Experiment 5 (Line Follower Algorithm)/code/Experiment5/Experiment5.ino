/*
 * SINGLE MOTOR LINE FOLLOWER USING MOTOR B (OUT3 & OUT4)
 * Motor connected to L298N Motor B outputs
 */

// ========== PIN DEFINITIONS ==========

// IR Sensor Pins
#define LEFT_IR    2
#define CENTER_IR  3
#define RIGHT_IR   4

// LED Indicator Pins
#define LEFT_LED   5    // Red LED
#define CENTER_LED 6    // Green LED
#define RIGHT_LED  7    // Blue LED

// Motor B Control Pins (OUT3 & OUT4)
#define MOTOR_ENB  9    // PWM Speed Control for Motor B
#define MOTOR_IN3 10    // Direction control 1 for Motor B
#define MOTOR_IN4 11    // Direction control 2 for Motor B

// ========== SYSTEM PARAMETERS ==========

// Motor Speed Settings (PWM 0-255)
const int SPEED_FORWARD = 200;     // Normal forward speed
const int SPEED_TURN = 180;        // Turning speed
const int SPEED_SLOW = 150;        // Slow speed for corrections
const int SPEED_STOP = 0;

// IR Sensor Logic (TCRT5000)
// LOW = Black line detected, HIGH = White surface
const int LINE_DETECTED = LOW;
const int NO_LINE = HIGH;

// Timing
const unsigned long DEBOUNCE_TIME = 50;
const unsigned long TURN_DURATION = 300;  // ms for turning

// ========== VARIABLES ==========
bool leftDetected = false;
bool centerDetected = false;
bool rightDetected = false;

unsigned long lastActionTime = 0;
String lastAction = "IDLE";

// ========== SETUP FUNCTION ==========
void setup() {
  Serial.begin(9600);
  Serial.println(F("========================================"));
  Serial.println(F("LINE FOLLOWER - MOTOR B (OUT3 & OUT4)"));
  Serial.println(F("========================================"));
  
  // Configure IR Sensors as INPUT
  pinMode(LEFT_IR, INPUT);
  pinMode(CENTER_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  
  // Configure LEDs as OUTPUT
  pinMode(LEFT_LED, OUTPUT);
  pinMode(CENTER_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  
  // Configure Motor B pins as OUTPUT
  pinMode(MOTOR_ENB, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  
  // Initial State
  digitalWrite(LEFT_LED, LOW);
  digitalWrite(CENTER_LED, LOW);
  digitalWrite(RIGHT_LED, LOW);
  motorStop();
  
  // Startup Sequence
  startupSequence();
  
  Serial.println(F("System Ready!"));
  Serial.println(F("Place IR sensors over black line"));
  Serial.println(F("L=Left, C=Center, R=Right sensors"));
  Serial.println(F("----------------------------------------"));
}

// ========== MAIN LOOP ==========
void loop() {
  // 1. Read Sensors
  readAllSensors();
  
  // 2. Update LED Indicators
  updateLEDIndicators();
  
  // 3. Display Sensor Status on Serial
  displaySensorStatus();
  
  // 4. Decision Making and Motor Control
  controlLogic();
  
  // 5. Small delay for stability
  delay(50);
}

// ========== SENSOR FUNCTIONS ==========

void readAllSensors() {
  // Read digital values from IR sensors
  leftDetected = (digitalRead(LEFT_IR) == LINE_DETECTED);
  centerDetected = (digitalRead(CENTER_IR) == LINE_DETECTED);
  rightDetected = (digitalRead(RIGHT_IR) == LINE_DETECTED);
}

void displaySensorStatus() {
  Serial.print(F("Sensors: ["));
  Serial.print(leftDetected ? F("L") : F("_"));
  Serial.print(F(" "));
  Serial.print(centerDetected ? F("C") : F("_"));
  Serial.print(F(" "));
  Serial.print(rightDetected ? F("R") : F("_"));
  Serial.print(F("] | Action: "));
  Serial.println(lastAction);
}

// ========== LED FUNCTIONS ==========

void updateLEDIndicators() {
  digitalWrite(LEFT_LED, leftDetected ? HIGH : LOW);
  digitalWrite(CENTER_LED, centerDetected ? HIGH : LOW);
  digitalWrite(RIGHT_LED, rightDetected ? HIGH : LOW);
}

// ========== MOTOR CONTROL FUNCTIONS ==========

void motorForward() {
  // Motor B Forward: IN3=HIGH, IN4=LOW
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
  analogWrite(MOTOR_ENB, SPEED_FORWARD);
  lastAction = "FORWARD";
}

void motorBackward() {
  // Motor B Backward: IN3=LOW, IN4=HIGH
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, HIGH);
  analogWrite(MOTOR_ENB, SPEED_SLOW);
  lastAction = "BACKWARD";
}

void motorStop() {
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
  analogWrite(MOTOR_ENB, SPEED_STOP);
  lastAction = "STOP";
}

void motorTurnLeft() {
  // For left turn: Stop briefly, then forward with boost
  motorStop();
  delay(150);
  
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
  analogWrite(MOTOR_ENB, SPEED_TURN + 40); // Extra boost for turn
  
  lastAction = "TURN LEFT";
  lastActionTime = millis();
}

void motorTurnRight() {
  // For right turn: Different timing pattern
  motorStop();
  delay(100);
  
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
  analogWrite(MOTOR_ENB, SPEED_TURN + 30);
  
  lastAction = "TURN RIGHT";
  lastActionTime = millis();
}

void motorSlowForward() {
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
  analogWrite(MOTOR_ENB, SPEED_SLOW);
  lastAction = "SLOW FWD";
}

// ========== DECISION LOGIC ==========

void controlLogic() {
  // Case 1: Only center sensor on line → Forward
  if (!leftDetected && centerDetected && !rightDetected) {
    motorForward();
  }
  
  // Case 2: Center and left on line → Slight left correction
  else if (leftDetected && centerDetected && !rightDetected) {
    motorSlowForward();
    lastAction = "SLIGHT LEFT";
  }
  
  // Case 3: Center and right on line → Slight right correction
  else if (!leftDetected && centerDetected && rightDetected) {
    motorSlowForward();
    lastAction = "SLIGHT RIGHT";
  }
  
  // Case 4: Only left sensor on line → Sharp left turn
  else if (leftDetected && !centerDetected && !rightDetected) {
    if (millis() - lastActionTime > TURN_DURATION) {
      motorTurnLeft();
    }
  }
  
  // Case 5: Only right sensor on line → Sharp right turn
  else if (!leftDetected && !centerDetected && rightDetected) {
    if (millis() - lastActionTime > TURN_DURATION) {
      motorTurnRight();
    }
  }
  
  // Case 6: All sensors on line → Intersection detected
  else if (leftDetected && centerDetected && rightDetected) {
    handleIntersection();
  }
  
  // Case 7: No sensors on line → Line lost
  else if (!leftDetected && !centerDetected && !rightDetected) {
    handleLineLost();
  }
  
  // Case 8: Left and right on line (center off) → Error state
  else if (leftDetected && !centerDetected && rightDetected) {
    motorStop();
    lastAction = "ERROR: L&R";
    errorBlink();
  }
}

// ========== SPECIAL CASE HANDLERS ==========

void handleIntersection() {
  Serial.println(F(">>> INTERSECTION DETECTED <<<"));
  
  // Stop motor
  motorStop();
  
  // Visual indication (blink all LEDs)
  for (int i = 0; i < 3; i++) {
    digitalWrite(LEFT_LED, HIGH);
    digitalWrite(CENTER_LED, HIGH);
    digitalWrite(RIGHT_LED, HIGH);
    delay(250);
    digitalWrite(LEFT_LED, LOW);
    digitalWrite(CENTER_LED, LOW);
    digitalWrite(RIGHT_LED, LOW);
    delay(250);
  }
  
  // Decision: Go straight (default)
  Serial.println(F("Decision: Continue straight"));
  delay(1000);
  
  // Cross intersection
  motorForward();
  delay(800);
  lastAction = "CROSS INTERSECTION";
}

void handleLineLost() {
  Serial.println(F(">>> LINE LOST - SEARCHING <<<"));
  
  // Stop first
  motorStop();
  delay(300);
  
  // Search pattern: Look left, then right
  digitalWrite(LEFT_LED, HIGH);
  delay(300);
  digitalWrite(LEFT_LED, LOW);
  
  digitalWrite(RIGHT_LED, HIGH);
  delay(300);
  digitalWrite(RIGHT_LED, LOW);
  
  // Try moving forward slowly to find line
  motorSlowForward();
  lastAction = "SEARCHING";
  
  // Search for 1 second
  unsigned long searchStart = millis();
  while (millis() - searchStart < 1000) {
    readAllSensors();
    if (leftDetected || centerDetected || rightDetected) {
      Serial.println(F("Line found!"));
      return;
    }
    delay(50);
  }
  
  // If still not found, try backward
  Serial.println(F("Trying backward search..."));
  motorBackward();
  delay(600);
  motorStop();
  
  lastAction = "LINE LOST";
}

void errorBlink() {
  // Blink center LED to indicate error
  for (int i = 0; i < 4; i++) {
    digitalWrite(CENTER_LED, HIGH);
    delay(100);
    digitalWrite(CENTER_LED, LOW);
    delay(100);
  }
}

// ========== STARTUP & TEST FUNCTIONS ==========

void startupSequence() {
  Serial.println(F("Starting system initialization..."));
  
  // Test LEDs
  Serial.println(F("Testing LEDs..."));
  testAllLEDs();
  
  // Test motor
  Serial.println(F("Testing Motor B (OUT3 & OUT4)..."));
  testMotorB();
  
  // Calibrate IR sensors
  Serial.println(F("IR Sensor Calibration:"));
  calibrateIRSensors();
  
  Serial.println(F("Initialization complete!"));
}

void testAllLEDs() {
  digitalWrite(LEFT_LED, HIGH);
  delay(200);
  digitalWrite(LEFT_LED, LOW);
  
  digitalWrite(CENTER_LED, HIGH);
  delay(200);
  digitalWrite(CENTER_LED, LOW);
  
  digitalWrite(RIGHT_LED, HIGH);
  delay(200);
  digitalWrite(RIGHT_LED, LOW);
  
  // All LEDs blink together
  digitalWrite(LEFT_LED, HIGH);
  digitalWrite(CENTER_LED, HIGH);
  digitalWrite(RIGHT_LED, HIGH);
  delay(300);
  digitalWrite(LEFT_LED, LOW);
  digitalWrite(CENTER_LED, LOW);
  digitalWrite(RIGHT_LED, LOW);
  
  delay(300);
}

void testMotorB() {
  Serial.println(F("  Forward test..."));
  motorForward();
  delay(800);
  
  Serial.println(F("  Stop test..."));
  motorStop();
  delay(500);
  
  Serial.println(F("  Backward test..."));
  motorBackward();
  delay(800);
  
  Serial.println(F("  Stop..."));
  motorStop();
  delay(500);
  
  Serial.println(F("Motor B test complete."));
}

void calibrateIRSensors() {
  Serial.println(F("Place all sensors on WHITE surface, then press any key..."));
  while (!Serial.available());
  Serial.read();
  
  readAllSensors();
  Serial.print(F("White surface readings: L="));
  Serial.print(leftDetected ? "LINE" : "NO  ");
  Serial.print(F(" C="));
  Serial.print(centerDetected ? "LINE" : "NO  ");
  Serial.print(F(" R="));
  Serial.print(rightDetected ? "LINE" : "NO  ");
  Serial.println(F(" (Should be NO NO NO)"));
  
  delay(2000);
  
  Serial.println(F("Place all sensors on BLACK line, then press any key..."));
  while (!Serial.available());
  Serial.read();
  
  readAllSensors();
  Serial.print(F("Black line readings: L="));
  Serial.print(leftDetected ? "LINE" : "NO  ");
  Serial.print(F(" C="));
  Serial.print(centerDetected ? "LINE" : "NO  ");
  Serial.print(F(" R="));
  Serial.print(rightDetected ? "LINE" : "NO  ");
  Serial.println(F(" (Should be LINE LINE LINE)"));
  
  Serial.println(F("Calibration complete."));
}

// ========== MANUAL TEST MODE ==========
// Uncomment to enable manual testing via Serial commands
/*
void serialEvent() {
  if (Serial.available()) {
    char cmd = Serial.read();
    
    switch(cmd) {
      case 'f': case 'F':
        motorForward();
        Serial.println("Manual: Forward");
        break;
      case 'b': case 'B':
        motorBackward();
        Serial.println("Manual: Backward");
        break;
      case 's': case 'S':
        motorStop();
        Serial.println("Manual: Stop");
        break;
      case 'l': case 'L':
        motorTurnLeft();
        Serial.println("Manual: Turn Left");
        break;
      case 'r': case 'R':
        motorTurnRight();
        Serial.println("Manual: Turn Right");
        break;
      case 't': case 'T':
        testMotorB();
        break;
      case '?':
        Serial.println("Commands: f=forward, b=backward, s=stop, l=left, r=right, t=test");
        break;
    }
  }
}
*/
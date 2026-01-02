/*
 * FINAL MOTOR CONTROL CODE
 * For 200-300 RPM Geared DC Motor with L298N
 * Optimized for Low, Medium, High Speeds
 * Using Motor B Channel (OUT3, OUT4)
 */

// Pin Definitions
#define IN3 8      // Direction control
#define IN4 9      // Direction control  
#define ENB 5      // PWM speed control (Motor B)

// Motor Parameters (CUSTOMIZE THESE FOR YOUR MOTOR)
const int MIN_PWM = 80;      // Minimum PWM to start motor (80 for 200-300 RPM)
const int MEDIUM_PWM = 140;  // Medium speed PWM
const int HIGH_PWM = 200;    // High speed PWM
const int FULL_PWM = 255;    // Full speed PWM

void setup() {
  // Set control pins as OUTPUT
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // CRITICAL: Optimize PWM frequency for L298N and geared motors
  // Changes Timer0 frequency to ~7.8kHz (from default 490Hz)
  // This gives smoother low-speed operation
  TCCR0B = TCCR0B & 0b11111000 | 0x02;
  
  Serial.begin(9600);
  Serial.println("========================================");
  Serial.println("GEARED MOTOR CONTROL - OPTIMIZED VERSION");
  Serial.println("Motor Spec: 200-300 RPM, 9-12V");
  Serial.println("========================================");
  delay(1000);
}

void loop() {
  // DEMONSTRATION SEQUENCE - All speed levels
  
  // 1. LOW SPEED (Noticeable rotation but slow)
  Serial.println("\n--- LOW SPEED ---");
  Serial.print("PWM: "); Serial.println(MIN_PWM);
  motorForward(MIN_PWM);
  delay(3000);
  
  // 2. MEDIUM SPEED
  Serial.println("\n--- MEDIUM SPEED ---");
  Serial.print("PWM: "); Serial.println(MEDIUM_PWM);
  motorForward(MEDIUM_PWM);
  delay(3000);
  
  // 3. HIGH SPEED
  Serial.println("\n--- HIGH SPEED ---");
  Serial.print("PWM: "); Serial.println(HIGH_PWM);
  motorForward(HIGH_PWM);
  delay(3000);
  
  // 4. FULL SPEED
  Serial.println("\n--- FULL SPEED ---");
  Serial.print("PWM: "); Serial.println(FULL_PWM);
  motorForward(FULL_PWM);
  delay(3000);
  
  // 5. STOP
  Serial.println("\n--- STOPPING ---");
  motorStop();
  delay(2000);
  
  // 6. REVERSE DEMO - All speeds
  Serial.println("\n=== REVERSE DIRECTION ===");
  
  Serial.println("\nReverse - Low Speed");
  motorReverse(MIN_PWM);
  delay(2000);
  
  Serial.println("\nReverse - Medium Speed");
  motorReverse(MEDIUM_PWM);
  delay(2000);
  
  Serial.println("\nReverse - High Speed");
  motorReverse(HIGH_PWM);
  delay(2000);
  
  // 7. FINAL STOP
  Serial.println("\n--- FINAL STOP ---");
  motorStop();
  delay(5000);  // Long pause before repeating
  
  // For viva/testing - you can also add this interactive mode:
  // Uncomment the next line for manual testing
  // testInteractiveMode();
}

// ============================================
// MOTOR CONTROL FUNCTIONS
// ============================================

void motorForward(int speedVal) {
  // Apply minimum threshold for geared motors
  if (speedVal < MIN_PWM && speedVal > 0) {
    speedVal = MIN_PWM;
    Serial.println("(Adjusted to minimum PWM)");
  }
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedVal);
  
  // Optional: Calculate approximate RPM for display
  int approxRPM = map(speedVal, MIN_PWM, 255, 50, 300);
  Serial.print("Approx RPM: ~"); Serial.println(approxRPM);
}

void motorReverse(int speedVal) {
  // Apply minimum threshold for geared motors
  if (speedVal < MIN_PWM && speedVal > 0) {
    speedVal = MIN_PWM;
    Serial.println("(Adjusted to minimum PWM)");
  }
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedVal);
  
  int approxRPM = map(speedVal, MIN_PWM, 255, 50, 300);
  Serial.print("Approx RPM: ~"); Serial.println(approxRPM);
}

void motorStop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  Serial.println("Motor Stopped");
}

void motorBrake() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 0);
  Serial.println("Motor Brake Applied");
}

// ============================================
// BONUS: INTERACTIVE TEST FUNCTION
// ============================================

void testInteractiveMode() {
  Serial.println("\n\nINTERACTIVE TEST MODE");
  Serial.println("Commands: F=Forward, R=Reverse, S=Stop, 0-9=Speed");
  Serial.println("Enter command in Serial Monitor");
  
  while (Serial.available() > 0) {
    char command = Serial.read();
    
    switch (command) {
      case 'F':
      case 'f':
        motorForward(MEDIUM_PWM);
        Serial.println("Forward - Medium Speed");
        break;
        
      case 'R':
      case 'r':
        motorReverse(MEDIUM_PWM);
        Serial.println("Reverse - Medium Speed");
        break;
        
      case 'S':
      case 's':
        motorStop();
        Serial.println("Stopped");
        break;
        
      case '0'...'9':
        int speedLevel = map(command - '0', 0, 9, MIN_PWM, 255);
        Serial.print("Speed Level: ");
        Serial.print(command);
        Serial.print(" -> PWM: ");
        Serial.println(speedLevel);
        // Keep current direction, change speed only
        int currentIN3 = digitalRead(IN3);
        int currentIN4 = digitalRead(IN4);
        digitalWrite(IN3, currentIN3);
        digitalWrite(IN4, currentIN4);
        analogWrite(ENB, speedLevel);
        break;
    }
  }
}
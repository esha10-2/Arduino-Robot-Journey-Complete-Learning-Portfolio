/*
 * SINGLE MOTOR OBSTACLE AVOIDANCE SYSTEM
 * Motor moves forward, stops/reverses when obstacle detected
 * LEDs indicate status
 */

// ========== PIN DEFINITIONS ==========
// Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 10;

// Single Motor Control (using Motor A on L298N)
const int enA = 3;     // ENABLE A (PWM speed control)
const int in1 = 5;     // Direction 1
const int in2 = 6;     // Direction 2

// LED Indicators
const int greenLED = 11;  // Clear path
const int redLED = 12;    // Obstacle detected

// ========== SYSTEM PARAMETERS ==========
const int OBSTACLE_DISTANCE = 20;   // Distance threshold in cm
const int FORWARD_SPEED = 180;      // PWM 0-255
const int REVERSE_SPEED = 160;      // PWM 0-255
const int REVERSE_TIME = 1000;      // ms to reverse
const int TURN_TIME = 800;          // ms to "turn" (actually pivot)

// Variables
long distance = 0;
unsigned long lastObstacleTime = 0;
bool isAvoiding = false;

// ========== SETUP ==========
void setup() {
  Serial.begin(9600);
  Serial.println("Single Motor Obstacle Avoidance System");
  Serial.println("======================================");
  
  // Configure Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Configure Motor pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Configure LED pins
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  // Initial state: STOPPED, Green LED ON
  stopMotor();
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  
  // Brief startup sequence
  startupSequence();
  
  Serial.println("System Ready!");
  Serial.println("Place obstacle within 20cm to test");
  Serial.println();
}

// ========== MAIN LOOP ==========
void loop() {
  // Measure distance
  distance = getDistance();
  
  // Display distance on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | ");
  
  // If currently avoiding obstacle, complete the maneuver
  if (isAvoiding) {
    Serial.println("Completing avoidance maneuver...");
    delay(100);
    return;
  }
  
  // Check for obstacle
  if (distance < OBSTACLE_DISTANCE && distance > 2) {
    // OBSTACLE DETECTED
    Serial.println("OBSTACLE! Taking action...");
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    
    // Execute avoidance sequence
    avoidObstacle();
    
    // Clear flags
    isAvoiding = false;
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    
    // Wait a moment before resuming
    delay(500);
  } 
  else {
    // CLEAR PATH - Move forward
    Serial.println("CLEAR - Moving forward");
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    moveForward();
  }
  
  delay(100); // Small delay between readings
}

// ========== ULTRASONIC FUNCTIONS ==========
long getDistance() {
  // Send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echo
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  
  // Calculate distance
  long distance = duration * 0.034 / 2;
  
  // Return valid distance or 999 if out of range
  if (distance <= 0 || distance > 400) {
    return 999;
  }
  return distance;
}

// ========== OBSTACLE AVOIDANCE SEQUENCE ==========
void avoidObstacle() {
  isAvoiding = true;
  
  Serial.println("=== AVOIDANCE SEQUENCE STARTED ===");
  
  // Step 1: STOP
  Serial.println("1. Stopping motor");
  stopMotor();
  delay(500);
  
  // Step 2: REVERSE
  Serial.println("2. Reversing for 1 second");
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
  moveBackward();
  delay(REVERSE_TIME);
  
  // Step 3: STOP briefly
  Serial.println("3. Brief pause");
  stopMotor();
  delay(300);
  
  // Step 4: "TURN" (Pivot in place by moving motor forward)
  Serial.println("4. Turning/Pivoting");
  moveForward();  // This will cause single-wheel turn
  delay(TURN_TIME);
  
  // Step 5: STOP
  Serial.println("5. Stop after turn");
  stopMotor();
  delay(300);
  
  Serial.println("=== AVOIDANCE SEQUENCE COMPLETE ===");
  isAvoiding = false;
}

// ========== MOTOR CONTROL FUNCTIONS ==========
void moveForward() {
  Serial.println("Motor: FORWARD");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, FORWARD_SPEED);
}

void moveBackward() {
  Serial.println("Motor: BACKWARD");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, REVERSE_SPEED);
}

void stopMotor() {
  Serial.println("Motor: STOP");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
}

// Pivot turn (simulated with single wheel)
void pivotTurn() {
  Serial.println("Motor: PIVOT TURN");
  // Rapid on/off to simulate searching
  for (int i = 0; i < 3; i++) {
    moveForward();
    delay(200);
    stopMotor();
    delay(100);
  }
}

// ========== STARTUP SEQUENCE ==========
void startupSequence() {
  Serial.println("Starting up...");
  
  // LEDs test
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  delay(500);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  delay(300);
  
  // Motor test sequence
  Serial.println("Testing motor...");
  
  // Forward test
  digitalWrite(greenLED, HIGH);
  moveForward();
  delay(800);
  stopMotor();
  delay(300);
  
  // Backward test
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  moveBackward();
  delay(800);
  stopMotor();
  delay(300);
  
  // Return to initial state
  stopMotor();
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
  
  Serial.println("Startup complete!");
}

// ========== MANUAL TEST FUNCTION ==========
void manualTest() {
  Serial.println("\n=== MANUAL TEST MODE ===");
  Serial.println("Press any key to start test...");
  while(!Serial.available());
  Serial.read();
  
  Serial.println("1. Testing FORWARD (3 sec)");
  moveForward();
  delay(3000);
  
  Serial.println("2. Testing BACKWARD (3 sec)");
  moveBackward();
  delay(3000);
  
  Serial.println("3. Testing OBSTACLE AVOIDANCE");
  avoidObstacle();
  
  Serial.println("4. Testing COMPLETE");
  stopMotor();
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  
  Serial.println("Returning to normal operation...");
  delay(1000);
}

// ========== EXTRA: ADD MANUAL TEST TRIGGER ==========
// Uncomment to enable manual testing with Serial command
/*
void serialEvent() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 't' || command == 'T') {
      manualTest();
    }
    if (command == 's' || command == 'S') {
      stopMotor();
      Serial.println("Motor STOPPED by user");
    }
  }
}
*/
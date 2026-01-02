/*
 * SERIAL-CONTROLLED MOTOR DRIVER
 * Commands:
 * F - Forward
 * B - Backward
 * L - Turn Left
 * R - Turn Right
 * S - Stop
 * 0-9 - Speed control (0=stop, 9=max)
 */

// Motor A connections
int enA = 5;
int in1 = 4;
int in2 = 3;

// Motor B connections
int enB = 6;
int in3 = 7;
int in4 = 8;

int motorSpeed = 150; // Default speed (0-255)

void setup() {
  // Set all motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Initialize motors to stop
  stopMotors();
  
  // Start serial communication
  Serial.begin(9600);
  delay(1000);
  
  // Display command menu
  Serial.println("==============================");
  Serial.println("   SERIAL MOTOR CONTROLLER   ");
  Serial.println("==============================");
  Serial.println("Commands:");
  Serial.println("  F  - Move Forward");
  Serial.println("  B  - Move Backward");
  Serial.println("  L  - Turn Left");
  Serial.println("  R  - Turn Right");
  Serial.println("  S  - Stop Motors");
  Serial.println("  0-9 - Set Speed (0=min, 9=max)");
  Serial.println("  C  - Current Status");
  Serial.println("==============================");
  Serial.println();
}

void loop() {
  // Check if data is available from Serial Monitor
  if (Serial.available() > 0) {
    char command = Serial.read();
    processCommand(command);
  }
}

void processCommand(char cmd) {
  switch(cmd) {
    case 'F':
    case 'f':
      moveForward();
      Serial.println("Moving FORWARD");
      break;
      
    case 'B':
    case 'b':
      moveBackward();
      Serial.println("Moving BACKWARD");
      break;
      
    case 'L':
    case 'l':
      turnLeft();
      Serial.println("Turning LEFT");
      break;
      
    case 'R':
    case 'r':
      turnRight();
      Serial.println("Turning RIGHT");
      break;
      
    case 'S':
    case 's':
      stopMotors();
      Serial.println("STOPPED");
      break;
      
    case '0' ... '9':
      // Convert char to number and map to PWM range
      int speedLevel = cmd - '0'; // Convert '5' to 5
      motorSpeed = map(speedLevel, 0, 9, 0, 255);
      analogWrite(enA, motorSpeed);
      analogWrite(enB, motorSpeed);
      Serial.print("Speed set to: ");
      Serial.println(speedLevel);
      break;
      
    case 'C':
    case 'c':
      displayStatus();
      break;
      
    case '\n':
    case '\r':
      // Ignore newline characters
      break;
      
    default:
      Serial.println("Invalid command! Type 'C' for commands");
      break;
  }
}

// ===== MOTOR CONTROL FUNCTIONS =====

void moveForward() {
  // Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  // Set speed
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void moveBackward() {
  // Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  // Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void turnLeft() {
  // Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  // Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
  
  // Turn for 500ms then stop
  delay(500);
  stopMotors();
}

void turnRight() {
  // Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
  
  delay(500);
  stopMotors();
}

void stopMotors() {
  // Turn all motors OFF
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void displayStatus() {
  Serial.println("\n=== CURRENT STATUS ===");
  Serial.print("Motor Speed: ");
  Serial.println(motorSpeed);
  Serial.print("PWM Value: ");
  Serial.println(map(motorSpeed, 0, 255, 0, 100));
  Serial.println("Ready for commands!");
  Serial.println("=====================\n");
}
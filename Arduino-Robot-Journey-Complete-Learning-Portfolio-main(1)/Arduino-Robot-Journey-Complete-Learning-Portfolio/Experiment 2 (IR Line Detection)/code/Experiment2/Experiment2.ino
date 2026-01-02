int leftIR = 6;
int centerIR = 7;
int rightIR = 8;

int ledPin = 3;

void setup() {
  pinMode(leftIR, INPUT);
  pinMode(centerIR, INPUT);
  pinMode(rightIR, INPUT);

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int L = digitalRead(leftIR);
  int C = digitalRead(centerIR);
  int R = digitalRead(rightIR);

  Serial.print("L: ");
  Serial.print(L);
  Serial.print(" C: ");
  Serial.print(C);
  Serial.print(" R: ");
  Serial.println(R);

  // If any sensor detects black line
  if (L == LOW || C == LOW || R == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Line Detected");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("No Line");
  }

  delay(200);
}
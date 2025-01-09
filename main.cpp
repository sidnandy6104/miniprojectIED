// Pin Definitions
const int leftSensorPin = A0;  // Left sensor connected to analog pin A0
const int rightSensorPin = A1; // Right sensor connected to analog pin A1
const int leftMotorPin1 = 3;   // Left motor control pin 1
const int leftMotorPin2 = 4;   // Left motor control pin 2
const int rightMotorPin1 = 5;  // Right motor control pin 1
const int rightMotorPin2 = 6;  // Right motor control pin 2

// Threshold for line detection
const int threshold = 500;

void setup() {
    // Set motor pins as outputs
    pinMode(leftMotorPin1, OUTPUT);
    pinMode(leftMotorPin2, OUTPUT);
    pinMode(rightMotorPin1, OUTPUT);
    pinMode(rightMotorPin2, OUTPUT);
    
    // Initialize serial communication for debugging
    Serial.begin(9600);
}

void loop() {
    // Read sensor values
    int leftSensorValue = analogRead(leftSensorPin);
    int rightSensorValue = analogRead(rightSensorPin);

    // Debugging output
    Serial.print("Left Sensor: ");
    Serial.print(leftSensorValue);
    Serial.print(" Right Sensor: ");
    Serial.println(rightSensorValue);

    // Line following logic
    if (leftSensorValue > threshold && rightSensorValue > threshold) {
        // Both sensors detect the line (robot is centered)
        moveForward();
    } else if (leftSensorValue > threshold && rightSensorValue <= threshold) {
        // Only left sensor detects the line (robot veering right)
        turnLeft();
    } else if (leftSensorValue <= threshold && rightSensorValue > threshold) {
        // Only right sensor detects the line (robot veering left)
        turnRight();
    } else {
        // No line detected (stop or search for the line)
        stopMotors();
    }
}

void moveForward() {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
}

void turnLeft() {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
}

void turnRight() {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
}

void stopMotors() {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
}

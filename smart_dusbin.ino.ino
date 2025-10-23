#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 6

Servo lidServo;

// Distance threshold in centimeters
const int OPEN_DISTANCE = 20;
const int OPEN_ANGLE = 90;     
const int CLOSE_ANGLE = 0;     

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lidServo.attach(SERVO_PIN);
  lidServo.write(CLOSE_ANGLE);
  Serial.println("Smart Dustbin Ready...");
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2; 
  return distance;
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance <= OPEN_DISTANCE) {
    lidServo.write(OPEN_ANGLE);
    Serial.println("Lid Opened");
    delay(3000); // Keep open for 3 seconds
    lidServo.write(CLOSE_ANGLE);
    Serial.println("Lid Closed");
    delay(1000);
  }

  delay(200);
}

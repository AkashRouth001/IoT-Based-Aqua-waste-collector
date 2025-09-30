#define TRIG_PIN 12
#define ECHO_PIN 11
#define LED_PIN 7 // For single LED setup
/*
ARDUINO NENO

Ultrasonic Sensor VCC->	5V
Ultrasonic Sensor GND	->GND
Ultrasonic Sensor Trig->	Digital Pin 12
Ultrasonic Sensor Echo->	Digital Pin 11
LED Positive	->Digital Pin 7 (with a resistor)
LED Negative	->GND

*/

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // Set LED as output
  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Light up LED if distance is less than a threshold (e.g., <20 cm)
  if (distance < 20) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(100); // Delay for stability
}

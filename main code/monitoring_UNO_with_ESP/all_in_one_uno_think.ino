#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

// Pin Definitions
#define TURBIDITY_PIN 36            // Turbidity Sensor (ESP32)
#define ONE_WIRE_BUS 5              // DS18B20 Temperature Sensor
#define PH_PIN A0                   // pH Sensor
#define TEMP_PIN A2                 // Analog Temperature Sensor
#define TRIG_PIN 12                 // Ultrasonic Sensor TRIG
#define ECHO_PIN 11                 // Ultrasonic Sensor ECHO
#define LED_PIN 7                   // LED Indicator (Water Level)
#define DHTPIN 2                    // DHT11 Sensor
#define DHTTYPE DHT11               // DHT11 Sensor Type
DHT dht(DHTPIN, DHTTYPE);

// Sensor Setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);       // Start Serial communication
  sensors.begin();          // Initialize DS18B20 temperature sensor
  dht.begin();              // Initialize DHT11 sensor
  pinMode(TRIG_PIN, OUTPUT); // Set Ultrasonic TRIG pin as output
  pinMode(ECHO_PIN, INPUT);  // Set Ultrasonic ECHO pin as input
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
}

void loop() {
  // **Turbidity Sensor**
  int sensorValue = analogRead(TURBIDITY_PIN);
  float turbidity = map(sensorValue, 0, 750, 100, 0); // Map sensor values to NTU
  turbidity = constrain(turbidity, 0, 100);            // Ensure value is within 0-100 range

  // **pH & Temperature Sensors**
  long phTot = 0, temTot = 0;
  for (int i = 0; i < 10; i++) {
    phTot += analogRead(PH_PIN);
    temTot += analogRead(TEMP_PIN);
    delay(10);
  }
  float phAvg = phTot / 10.0;
  float temAvg = temTot / 10.0;
  float phVoltage = phAvg * (5.0 / 1023.0);
  float tempVoltage = temAvg * (5000.0 / 1023.0);
  float pHValue = phVoltage * -5.70 + 21.34; // Convert to pH scale
  sensors.requestTemperatures();
  float waterTemp = sensors.getTempCByIndex(0); // Get temperature from DS18B20

  // **Ultrasonic Sensor (Water Level)**
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(1);//old->2
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(2);//old->10
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; // Calculate distance to water surface

  // **LED Control for Water Level**
  digitalWrite(LED_PIN, distance < 50 ? HIGH : LOW); // LED ON if water level is low

  // **DHT11 Sensor (Air Temp & Humidity)**
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();
  
  // Prepare data to send via Serial
  String data = String(pHValue) + "," + String(turbidity) + "," + String(waterTemp) + "," + String(distance) + "," + String(temperatureC) + "," + String(humidity);

  // Send data to ESP8266 via Serial
  Serial.println(data);

  // Print values for debugging
  Serial.print("Turbidity: "); Serial.print(turbidity); Serial.println(" NTU");
  Serial.print("pH Value: "); Serial.println(pHValue);
  //Serial.print("Water Temp: "); Serial.print(waterTemp); Serial.println(" C");
  Serial.print("Object Distance: "); Serial.print(distance); Serial.println(" cm");
  Serial.print("Air Temp: "); Serial.print(temperatureC); Serial.println(" C");
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.println("--------------------");
  
  delay(2000); // Delay for 2 seconds before next reading
}

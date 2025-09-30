#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

// Turbidity Sensor (ESP32)
#define TURBIDITY_PIN 36

// pH & Temperature Sensor (Arduino)
#define ONE_WIRE_BUS 5 // DS18B20 Temperature Sensor
#define PH_PIN A0      // pH Sensor
#define TEMP_PIN A2    // Analog Temperature Sensor

// Ultrasonic Sensor & LED (Arduino)
#define TRIG_PIN 12
#define ECHO_PIN 11
#define LED_PIN 7

// DHT11 Temperature & Humidity Sensor (Arduino)
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
    Serial.begin(9600);
    sensors.begin();
    dht.begin();
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // **Turbidity Sensor**
    int sensorValue = analogRead(TURBIDITY_PIN);
    float turbidity = map(sensorValue, 0, 750, 100, 0);
    turbidity = constrain(turbidity, 0, 100);
    Serial.print("Turbidity: ");
    Serial.print(turbidity);
    Serial.println(" NTU");

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
    float pHValue = phVoltage * -5.70 + 21.34;
    sensors.requestTemperatures();
    float waterTemp = sensors.getTempCByIndex(0);
    Serial.print("pH Value: "); Serial.println(pHValue);
    Serial.print("Water Temperature: "); Serial.print(waterTemp); Serial.println(" C");

    // **Ultrasonic Sensor & LED**
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration * 0.034 / 2;
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
    digitalWrite(LED_PIN, distance < 20 ? HIGH : LOW);

    // **DHT11 Sensor**
    float humidity = dht.readHumidity();
    float temperatureC = dht.readTemperature();
    float temperatureF = dht.readTemperature(true);
    float temperatureK = temperatureC + 273.15;
    Serial.print("Temperature: "); Serial.print(temperatureC);
    Serial.print(" C, "); Serial.print(temperatureF);
    Serial.print(" F, "); Serial.print(temperatureK);
    Serial.println(" K");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println("%");
    Serial.println("--------------------");
    Serial.println("--------------------");
    delay(2000);
}

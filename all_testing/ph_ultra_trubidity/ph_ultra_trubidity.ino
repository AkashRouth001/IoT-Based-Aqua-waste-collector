#include <OneWire.h>
#include <DallasTemperature.h>

// Turbidity Sensor (ESP32)
#define TURBIDITY_SENSOR_PIN 36
int turbidityValue = 0;
float turbidity = 0;

// pH & Temperature Sensors
#define ONE_WIRE_BUS 5
const int analogPhPin = A0;
const int analogTemPin = A2;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
const float C = 21.34;
const float m = -5.70;

// Ultrasonic Sensor & LED
#define TRIG_PIN 12
#define ECHO_PIN 11
#define LED_PIN 7

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    sensors.begin();
    Serial.println("Sensor System Initialized");
}

void loop() {
    readTurbidity();
    readPHandTemperature();
    readUltrasonicSensor();
    delay(1000);
}

void readTurbidity() {
    turbidityValue = analogRead(TURBIDITY_SENSOR_PIN);
    turbidity = map(turbidityValue, 0, 750, 100, 0);
    turbidity = constrain(turbidity, 0, 100);
    Serial.print("Turbidity: ");
    Serial.print(turbidity);
    Serial.print(" NTU => ");
    if (turbidity < 20) Serial.println("CLEAR");
    else if (turbidity < 50) Serial.println("CLOUDY");
    else Serial.println("DIRTY");
}

void readPHandTemperature() {
    long phTot = 0, temTot = 0;
    for (int i = 0; i < 10; i++) {
        phTot += analogRead(analogPhPin);
        temTot += analogRead(analogTemPin);
        delay(10);
    }
    float temAvg = temTot / 10.0;
    float phAvg = phTot / 10.0;
    float temVoltage = temAvg * (5000.0 / 1023.0);
    float phVoltage = phAvg * (5.0 / 1023.0);
    sensors.requestTemperatures();
    float Etemp = temVoltage * 0.1;
    float pHValue = phVoltage * m + C;
    float Wtemp = sensors.getTempCByIndex(0);
    Serial.print("Environment Temp: "); Serial.print(Etemp); Serial.println(" C");
    Serial.print("Solution Temp: "); Serial.print(Wtemp); Serial.println(" C");
    Serial.print("pH Value: "); Serial.println(pHValue);
}

void readUltrasonicSensor() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(LED_PIN, (distance < 20) ? HIGH : LOW);
    Serial.println("-------------");
}


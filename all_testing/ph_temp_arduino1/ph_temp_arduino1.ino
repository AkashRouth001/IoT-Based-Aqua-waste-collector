/*void setup() {
    Serial.begin(9600); // Initialize Serial Monitor
}

void loop() {
    int sensorValue = analogRead(A0);

    // Convert the analog reading (0 - 1023) to voltage (0 - 5V)
    float voltage = sensorValue * (5.0 / 1023.0);

    // Display voltage value in Serial Monitor
    Serial.print("Voltage: ");
    Serial.print(voltage, 2); // Display voltage with 2 decimal places
    Serial.println(" V");

    delay(500);  // Delay for stable reading
}*/

// link -> https://bestengineeringprojects.com/arduino-ph-meter-using-ph-sensor/#google_vignette
//Header declarations
// ph senser 
#include <OneWire.h> 
#include <DallasTemperature.h> 
#include <math.h>
/*
t1 = a1
t2 = d5
p0 = a0

*/
//Pin Assignment
#define ONE_WIRE_BUS 5 // DS18B20 connected to digital pin D5
const int analogPhPin = A0; // PH module connected to analog pin A0
const int analogTemPin = A2; // Temperature module connected to analog pin A2

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 

// Constants for pH calculation
const float C = 21.34; 
const float m = -5.70; 

void setup() {
    Serial.begin(9600); // Initialize Serial Monitor
    sensors.begin(); // Start the DS18B20 Library
    Serial.println("PH and Temperature Monitoring");
}

void loop() {
    long phTot = 0, temTot = 0;
    float phAvg, temAvg;

    // Taking 10 samples for accurate reading
    for(int x = 0; x < 10; x++) {
        phTot += analogRead(analogPhPin);
        temTot += analogRead(analogTemPin);
        delay(10);
    }

    // Calculating average values
    temAvg = temTot / 10.0;
    phAvg = phTot / 10.0;

    // Converting sensor readings to voltage
    float temVoltage = temAvg * (5000.0 / 1023.0);
    float phVoltage = phAvg * (5.0 / 1023.0);

    sensors.requestTemperatures(); // Send command to get temperatures
    float Etemp = temVoltage * 0.1; // Convert to Celsius
    float pHValue = phVoltage * m + C;
    float Wtemp = sensors.getTempCByIndex(0);

    // Display results in Serial Monitor
    Serial.print("Environment Temp: ");
    Serial.print(Etemp);
    Serial.println(" C");

    Serial.print("Solution Temp: ");
    Serial.print(Wtemp);
    Serial.println(" C");

    Serial.print("pH Value of Solution: ");
    Serial.println(pHValue);

    delay(1000); // Delay before refreshing readings
}


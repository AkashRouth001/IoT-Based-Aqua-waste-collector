#include "DHT.h"

#define DHTPIN 2      // Pin where the sensor is connected
#define DHTTYPE DHT11 // Sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Serial to ESP8266
  dht.begin();        // Start the DHT sensor
}

void loop() {
  float humidity = dht.readHumidity();           // Read humidity
  float temperatureC = dht.readTemperature();    // Temperature in Celsius

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Error reading from DHT sensor!");
    return;
  }

  // Send temp and humidity in format: temp,hum
  Serial.print(temperatureC);
  Serial.print(",");
  Serial.println(humidity);  // Adds newline \n automatically

  delay(20000); // Match ThingSpeak interval in ESP8266
}

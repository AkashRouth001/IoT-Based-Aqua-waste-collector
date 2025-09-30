#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "Annie's Pixel";             // Your Wi-Fi name
const char* password = "blablabla";            // Your Wi-Fi password

unsigned long myChannelNumber = 2946491;       // ThingSpeak Channel ID
const char* myWriteAPIKey = "0HSRIF5FXOC0667G"; // ThingSpeak Write API Key

WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  ThingSpeak.begin(client);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.println("Received: " + data);

    float ph, turbidity, waterTemp, level, airTemp, humidity;
    int i = 0;

    ph = data.substring(i, data.indexOf(",", i)).toFloat(); i = data.indexOf(",", i) + 1;
    turbidity = data.substring(i, data.indexOf(",", i)).toFloat(); i = data.indexOf(",", i) + 1;
    waterTemp = data.substring(i, data.indexOf(",", i)).toFloat(); i = data.indexOf(",", i) + 1;
    level = data.substring(i, data.indexOf(",", i)).toFloat(); i = data.indexOf(",", i) + 1;
    airTemp = data.substring(i, data.indexOf(",", i)).toFloat(); i = data.indexOf(",", i) + 1;
    humidity = data.substring(i).toFloat();

    ThingSpeak.setField(1, ph);
    ThingSpeak.setField(2, turbidity);
    ThingSpeak.setField(3, waterTemp);
    ThingSpeak.setField(4, level);
    ThingSpeak.setField(5, airTemp);
    ThingSpeak.setField(6, humidity);

    int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (response == 200) {
      Serial.println("Data sent to ThingSpeak.");
    } else {
      Serial.print("Error code: "); Serial.println(response);
    }
  }
  delay(2000);
}

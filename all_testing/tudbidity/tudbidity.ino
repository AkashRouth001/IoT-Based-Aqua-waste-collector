// turbi dity 
int sensorPin = 36;  // Pin for ESP32
int sensorValue = 0; 
float turbidity = 0; 

void setup() {  
  Serial.begin(9600); 
}

void loop() { 
  sensorValue = analogRead(sensorPin);  // Read sensor value

  // Map sensor value to turbidity range
  turbidity = map(sensorValue, 0, 750, 100, 0); 

  // Clip turbidity values to ensure proper NTU range
  if (turbidity < 0) turbidity = 0; 
  if (turbidity > 100) turbidity = 100; 

  // Print turbidity value with water quality status
  Serial.print("Turbidity: ");
  Serial.print(turbidity);
  Serial.print(" NTU => ");

  if (turbidity < 20) {
    Serial.println("CLEAR");
  }  
  else if (turbidity >= 20 && turbidity < 50) {
    Serial.println("CLOUDY");
  }  
  else {
    Serial.println("DIRTY");
  }

  delay(1000);  // Wait before next reading
}

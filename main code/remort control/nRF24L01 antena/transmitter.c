#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define JOYSTICK1_Y A1
#define JOYSTICK2_Y A3
RF24 radio(9, 10); // CE=9, CSN=10
const byte address[6] = "00001";
struct JoystickData {
int leftMotor; // Speed -255 to 255
int rightMotor; // Speed -255 to 255
};
JoystickData data;
void setup() {
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MAX);
radio.stopListening();
Serial.println("Transmitter started with PWM speed control");
}
int applyDeadzone(int val, int deadzone) {
if (abs(val - 512) < deadzone) return 512; // Center value for no movement
return val;
}
void loop() {
int leftVal = analogRead(JOYSTICK1_Y);
int rightVal = analogRead(JOYSTICK2_Y);
// Apply deadzone
leftVal = applyDeadzone(leftVal, 50);
rightVal = applyDeadzone(rightVal, 50);
// Map analog values (0-1023) to speed (-255 to 255)
data.leftMotor = map(leftVal, 0, 1023, -255, 255);
data.rightMotor = map(rightVal, 0, 1023, -255, 255);
bool success = radio.write(&data, sizeof(data));
// Serial debug output
Serial.print("Left Joystick: ");
Serial.print(leftVal);
Serial.print(" | Left Motor Speed: ");
Serial.print(data.leftMotor);
Serial.print(" | Right Joystick: ");
Serial.print(rightVal);
Serial.print(" | Right Motor Speed: ");
Serial.print(data.rightMotor);
Serial.print(" | Send status: ");
Serial.println(success ? "Success" : "Failed");
delay(50); }

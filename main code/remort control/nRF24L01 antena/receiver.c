#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// Motor A (Left)
#define MOTOR_A_IN1 2
#define MOTOR_A_IN2 3
#define MOTOR_A_EN 9 // PWM pin
// Motor B (Right)
#define MOTOR_B_IN1 4
#define MOTOR_B_IN2 5
#define MOTOR_B_EN 10 // PWM pin
RF24 radio(7, 8); // CE=7, CSN=8
const byte address[6] = "00001";
struct JoystickData {
int leftMotor; // Speed -255 to 255
int rightMotor; // Speed -255 to 255
};
JoystickData data;
void setup() {
Serial.begin(9600);
pinMode(MOTOR_A_IN1, OUTPUT);
pinMode(MOTOR_A_IN2, OUTPUT);
pinMode(MOTOR_A_EN, OUTPUT);
pinMode(MOTOR_B_IN1, OUTPUT);
pinMode(MOTOR_B_IN2, OUTPUT);
pinMode(MOTOR_B_EN, OUTPUT);
radio.begin();
radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MAX);
radio.startListening();
Serial.println("Receiver started with PWM motor control");
}
void loop() {
if (radio.available()) {
radio.read(&data, sizeof(data));
Serial.print("Received Left Motor Speed: ");
Serial.print(data.leftMotor);
Serial.print(" | Right Motor Speed: ");
Serial.println(data.rightMotor);
setMotor(MOTOR_A_IN1, MOTOR_A_IN2, MOTOR_A_EN, data.leftMotor);
setMotor(MOTOR_B_IN1, MOTOR_B_IN2, MOTOR_B_EN, data.rightMotor);
}
}
void setMotor(int in1, int in2, int en, int speed) {
speed = constrain(speed, -255, 255);
if (speed > 0) {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(en, speed);
} else if (speed < 0) {
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
analogWrite(en, -speed);
} else {
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
analogWrite(en, 0);
}
}

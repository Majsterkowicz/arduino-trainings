#include <Arduino.h>
#include <Wire.h>
/*   
 *   Basic example code for controlling a stepper without library
 *      
 *   by Dejan, https://howtomechatronics.com
 */

// defines pins
#define stepPin 5
#define dirPin 2 
#define dirLed 3

unsigned int rotDelay = 700;
int pulsesPerRotate = 100;
int microstepping = 2;
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT);
  pinMode(dirLed, OUTPUT);
}
void loop() {
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  digitalWrite(dirLed, HIGH);
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < (pulsesPerRotate * microstepping * 1); x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(rotDelay);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW);
    delayMicroseconds(rotDelay); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  digitalWrite(dirLed, LOW);
  for(int x = 0; x < (pulsesPerRotate * microstepping * 4); x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(rotDelay);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(rotDelay);
  }
  delay(1000);
}
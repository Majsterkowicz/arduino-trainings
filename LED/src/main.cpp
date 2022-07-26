#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(7,INPUT_PULLUP);
  digitalWrite(13,LOW);
}

void loop() {
  if (digitalRead(7) == LOW)
  {
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
  }
  else
  {
    digitalWrite(13,HIGH);
  }
  
  
  // put your main code here, to run repeatedly:
}
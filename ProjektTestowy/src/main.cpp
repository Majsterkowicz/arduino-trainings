/*
Blink
Turning LED on and off
*/

#include <Arduino.h>
int i;

void setup() {
  // put your setup code here, to run once:
  ///initialize LED digital pin as an output
  pinMode(13, OUTPUT);
  pinMode(7,INPUT_PULLUP);
  digitalWrite(13,LOW);
  }

void loop() {
  // put your main code here, to run repeatedly:
    //turn the LED on
   digitalWrite(13, HIGH); //świecenie ciągłe
   delay(2000);

   while (digitalRead(7) == HIGH) {}  //program kreci się w kółko, dioda 100%

   delay(200);  //odczekanie 200ms po wciśnięciu przycisku

   while (digitalRead(7) == HIGH)  //wejście w pętlę, dopóki przycisk niewcisnięty
   {  //dioda na 50%
  digitalWrite(13,HIGH);
  delay(5);
  digitalWrite(13,LOW);
  delay(5);
   }

   delay(200); //odczekanie 200ms

while (digitalRead(7) == HIGH)  //wejście w pętlę, dopóki przycisk niewcisnięty
   {  //dioda na 25%
  digitalWrite(13,HIGH);
  delay(2);
  digitalWrite(13,LOW);
  delay(6);
   }

   delay(200);

while (digitalRead(7) == HIGH)  //wejście w pętlę, dopóki przycisk niewcisnięty
   {  //dioda na 5%
  digitalWrite(13,HIGH);
  delay(1);
  digitalWrite(13,LOW);
  delay(19);
   }

   delay(200);


  }
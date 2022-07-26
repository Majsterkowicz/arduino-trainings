#include <Arduino.h>
#include <Servo.h>  
int odczyt = 0;       //odczyt z portu analogowego
Servo serwomechanizm;  //tworzymy obiekt typu serwomechanizm
int pozycja = 0;      // pozycja serwomechnizmu

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  }

void loop() {
   odczyt = analogRead(A5);
   odczyt = map(odczyt, 0, 1022, 1, 5);

   if (odczyt <= 1)
   {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
   }
   else if (odczyt <= 2)
   {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
   }
   else if (odczyt <= 3)
   {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
   }
   else if (odczyt <= 4)
   {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
   }
else if (odczyt == 5)
   {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
   }
   delay(100);
}
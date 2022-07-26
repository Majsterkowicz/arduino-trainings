#include <Arduino.h>
#include <Servo.h>  
int odczyt = 0;       //odczyt z portu analogowego
Servo serwomechanizm;  //tworzymy obiekt typu serwomechanizm
int pozycja = 0;      // pozycja serwomechnizmu
int  pozycja_poprzednia = 0; //domyślna pozycja poprzednia na zero

void setup() {
  pinMode(8, OUTPUT);  //konfiguracja pinów pod LED
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  serwomechanizm.attach(6);  //serwomechanizm podłączony pod pin 6 PWM
  Serial.begin(9600);  //uruchomienie UART
  }

void loop() {
   odczyt = analogRead(A5);  // odczyt wartości z potencjometru/czujnika
   //odczyt = map(odczyt, 0, 1020, 1, 5);   //mapowanie odczytu z potencjometru na podziałce 0-1020 na wartości 1-5
   pozycja = map(odczyt, 0, 1020, 300, 2000);   //mapowanie odczytu z potencjometru na podziałce 0-1020 na wartości 450-2000 dla małego serwa
   if (abs(pozycja - pozycja_poprzednia) > 100) {  //sprawdzenie, czy pozycja obecna jest większa o 5 od poprzedniej
   serwomechanizm.writeMicroseconds(pozycja);   //wykonanie ruchu
   delay(500);  //opóźnienie
   pozycja_poprzednia = pozycja;  //podpisanie poprzedniej pozycji jako obecnej
   }

   /*
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
   delay(100); */
}
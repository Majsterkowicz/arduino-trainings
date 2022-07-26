#include <Arduino.h>
#include <Servo.h>
#define przyciskUP 7
#define przyciskDOWN 8
#define LED 13
#define START 10

Servo serwomechanizm;  //tworzymy obiekt typu serwomechanizm
int pozycja = 0; //aktualna pozycja serwomechanizmu
int zmiana = 6; //podziałka zmiany pozycji serwomechnizmu w stopniach
int pozycjaMIN = 450;
int pozycjaMAX = 2000;


void setup()
{
  pinMode(przyciskUP,INPUT_PULLUP);
  pinMode(przyciskDOWN,INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  serwomechanizm.attach(9);
  digitalWrite(LED, LOW);
  while (digitalRead(START) == HIGH) {}
  
  
}

void loop() {
  // if (digitalRead(przyciskUP == HIGH)){
  //   pozycja = pozycja + zmiana;
  //   serwomechanizm.write(pozycja);
  // }
  // if (digitalRead(przyciskDOWN == LOW)){
  //   pozycja = pozycja - zmiana;
  //   serwomechanizm.write(pozycja);
  // }
  for (pozycja = pozycjaMIN; pozycja <= pozycjaMAX; pozycja += 10)
  {
    serwomechanizm.writeMicroseconds(pozycja);
    delay(20);
    if (pozycja == pozycjaMIN)
    {
      digitalWrite(LED, HIGH);
      delay(1000);
      
    }
    digitalWrite(LED, LOW);
    
  }
  for (pozycja = pozycjaMAX; pozycja >= pozycjaMIN; pozycja -= 10)
  {
    serwomechanizm.writeMicroseconds(pozycja);
    delay(20);
    if (pozycja == pozycjaMAX)
    {
      digitalWrite(LED, HIGH);
      delay(1000);
    }
    digitalWrite(LED, LOW);
  }
  
}
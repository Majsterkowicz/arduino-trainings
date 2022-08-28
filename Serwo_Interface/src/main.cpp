#include <Arduino.h>
#include <Wire.h>  //biblioteka Wires, potrzebna do prawidłowego kompilowania programu (?)
#include <Servo.h> //biblioteka do obłsugi serwomechanizmów
#include <LiquidCrystal.h> //biblioteka do obsługi wyświetlaczy LCD
#define przyciskUp 8  //
#define przyciskDown 11  // Przyciski sterujące
#define przyciskOK 12  //
#define czerwony A0  //
#define zielony A1  // deklaracja podpięcia diody RGB pod piny analogowe
#define niebieski A2 //
#define testLED 13
#define refButton 10
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //informacja o podłączeniu wyświetlacza, pod jakie piny
Servo serwomechanizm;
int pozycja = 1100;
int zmianaPoz = 10;
int pozMin = 450;
int pozMax = 2000;
int stanLed = HIGH;
unsigned long aktualnyCzas = 0;
unsigned long zapisanyCzas = 0;
const int kolorCzerwony = 1;
const int kolorZielony = 2;
const int kolorNiebieski = 3;
int stanLED = HIGH;
// int color = 0;

void setup()
{
  digitalWrite(czerwony, HIGH);
  digitalWrite(zielony, HIGH);
  digitalWrite(niebieski,HIGH);
  digitalWrite(testLED, LOW);
  serwomechanizm.attach(9);  //deklaracja podłączenia serwomechanizmu do pinu
  serwomechanizm.writeMicroseconds(pozycja);
  pinMode(przyciskUp,INPUT_PULLUP);
  pinMode(przyciskDown, INPUT_PULLUP); // deklaracja pinów i ustawienie jako przyciski
  pinMode(przyciskOK, INPUT_PULLUP);
  pinMode(czerwony, OUTPUT);
  pinMode(zielony,OUTPUT);   // ustawienie pinów jako Output
  pinMode(niebieski,OUTPUT);
  pinMode(refButton, INPUT_PULLUP);
  pinMode(testLED, OUTPUT);
  lcd.begin(16, 2); //Deklaracja typu wyświetlacza
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Ekran powitalny"); //Wyświetlenie tekstu powitalnego
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("Bazowac naped?"); //Wyświetlenie tekstu z zapytaniem o bazowanie, 10 znaków
}


void LEDblink(int color)
{
  switch (color)
  {
  case kolorCzerwony:
    stanLed = !stanLed;
    digitalWrite(czerwony, stanLed);
    break;
  case kolorZielony:
    stanLed = !stanLed;
    digitalWrite(czerwony, stanLed);
    break;
  case kolorNiebieski:
    stanLed = !stanLed;
    digitalWrite(czerwony, stanLed);
    break;
  default:
    break;
  }
}

void LEDtest()
{
  aktualnyCzas = millis();
  if (aktualnyCzas - zapisanyCzas >= 1000UL)
  {
    zapisanyCzas = aktualnyCzas;
    LEDblink(kolorCzerwony);
    //stanLED = !stanLED;
    //digitalWrite(czerwony, stanLED);
  }
    
  // digitalWrite(czerwony, LOW);  //
  // delay(1000);                  //
  // digitalWrite(czerwony, HIGH); //
  // digitalWrite(zielony, LOW);   //
  // delay(1000);                  //  Test diodek RGB
  // digitalWrite(zielony, HIGH);  //
  // digitalWrite(niebieski, LOW); //
  // delay(1000);                  //
  // digitalWrite(niebieski,HIGH); //
}


void loop()
{
  LEDtest();
  if (digitalRead(przyciskOK) == LOW)
  {
    digitalWrite(testLED, HIGH);
  }
  else
  {
    digitalWrite(testLED, LOW);
  }

}
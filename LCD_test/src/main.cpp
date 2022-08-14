#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#define jasnoscWyswietlacza 11
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int odczyt;
int odczytRef;
double volty;
int jasnosc = 0;
int licznik = 0;

void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Odczyt napiecia:"); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("0.00V L="); //Wyświetlenie tekstu
  //lcd.blink();
}

void loop() {
odczyt = analogRead(A0);
if (abs(odczyt - odczytRef) >= 20 )
{
  volty = odczyt*5.00/1040.00;
lcd.setCursor(0,1);
lcd.print(volty);
lcd.setCursor(8,1);
lcd.print(licznik);

jasnosc = map(odczyt, 0, 1040, 0, 255);
analogWrite(jasnoscWyswietlacza, jasnosc);
odczytRef = odczyt;
licznik = licznik +1;
}

delay(250);
}
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int odczyt = 0;
byte przycisk;


void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Wcisnales przycisk:");
}

byte jaki_przycisk (int input)
{
  return map (input, 10, 900, 1, 3);
}

void loop() {
  odczyt = analogRead(A0);
  if (odczyt >= 300)
  {
    przycisk = jaki_przycisk (odczyt);
  }
  else
  {
    przycisk = 0;
  }
  lcd.setCursor(0,1);
  lcd.print(przycisk);
  lcd.setCursor(2,1);
  lcd.print(odczyt);
}
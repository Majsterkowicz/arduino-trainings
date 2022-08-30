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
#define przyciskRef 10
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //informacja o podłączeniu wyświetlacza, pod jakie piny
Servo serwomechanizm;
int pozycja = 1150;
int zmianaPoz = 10;
const int pozMin = 400;
const int pozMax = 2000;
int pozRefMin = 0;
int pozRefMax = 0;
int stanLed = HIGH;
const int min = 0;
const int max = 1;
unsigned long aktualnyCzas = 0;
unsigned long zapisanyCzas = 0;
const int kolorCzerwony = 1;
const int kolorZielony = 2;
const int kolorNiebieski = 3;
int stanLED = HIGH;
int wybor = 0;
bool baza = false;
// int color = 0;

void powitanie()
{
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Ekran powitalny"); //Wyświetlenie tekstu powitalnego
  lcd.setCursor(0, 1);
  lcd.print("Wcisnij OK");
  lcd.blink();
   while (digitalRead(przyciskOK) == HIGH){
   }
  lcd.clear();
  delay(1000);
  lcd.noBlink();
}

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
  pinMode(przyciskRef, INPUT_PULLUP);
  pinMode(testLED, OUTPUT);
  lcd.begin(16, 2); //Deklaracja typu wyświetlacza
  powitanie();
  }

int bazowanie (int dir)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Trwa bazowanie");
  lcd.setCursor(0, 1);
  //lcd.blink();
  digitalWrite(niebieski, LOW);
  
  switch (dir)
  {
    case 0:
      while (digitalRead(przyciskRef) == HIGH)
      {
      serwomechanizm.writeMicroseconds(pozycja);
      pozycja = pozycja - zmianaPoz;
      delay(50);
        if (pozycja <= pozMin)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Blad bazowania");
        }
      }
      while (digitalRead(przyciskRef) == LOW)
      {
      pozycja = pozycja + zmianaPoz;
      serwomechanizm.writeMicroseconds(pozycja);
      delay(200);
      }
    break;

    case 1:
      while (digitalRead(przyciskRef) == HIGH)
      {
      serwomechanizm.writeMicroseconds(pozycja);
      pozycja = pozycja + zmianaPoz;
      delay(50);
        if (pozycja >= pozMax)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Blad bazowania");
        }
      }
      while (digitalRead(przyciskRef) == LOW)
      {
      pozycja = pozycja - zmianaPoz;
      serwomechanizm.writeMicroseconds(pozycja);
      delay(200);
      }
    break;

    default:
    break;
  }
  digitalWrite(niebieski, HIGH);
  return pozycja;
}

// void LEDblink(int color)
// {
//   switch (color)
//   {
//   case kolorCzerwony:
//     stanLed = !stanLed;
//     digitalWrite(czerwony, stanLed);
//     break;
//   case kolorZielony:
//     stanLed = !stanLed;
//     digitalWrite(zielony, stanLed);
//     break;
//   case kolorNiebieski:
//     stanLed = !stanLed;
//     digitalWrite(niebieski, stanLed);
//     break;
//   default:
//     break;
//   }
// }

// void LEDtest()
// {
//   aktualnyCzas = millis();
//   if (aktualnyCzas - zapisanyCzas >= 1000UL)
//   {
//     zapisanyCzas = aktualnyCzas;
//     stanLed = !stanLed;
//     digitalWrite(zielony, stanLed);
//     //LEDblink(kolorNiebieski);
//     //stanLED = !stanLED;
//     //digitalWrite(czerwony, stanLED);
//   }
    
//   // digitalWrite(czerwony, LOW);  //
//   // delay(1000);                  //
//   // digitalWrite(czerwony, HIGH); //
//   // digitalWrite(zielony, LOW);   //
//   // delay(1000);                  //  Test diodek RGB
//   // digitalWrite(zielony, HIGH);  //
//   // digitalWrite(niebieski, LOW); //
//   // delay(1000);                  //
//   // digitalWrite(niebieski,HIGH); //
// }

void loop()
{
  if (baza == false)
  {
    lcd.setCursor(0, 0); //Ustawienie kursora
    lcd.print("Wcisnij OK"); //Wyświetlenie tekstu z zapytaniem o bazowanie, 10 znaków
    lcd.setCursor(0, 1); //Ustawienie kursora
    lcd.print("aby bazowac");
    while (digitalRead(przyciskOK) == HIGH)
    {
      /* code */
    }
    if (digitalRead(przyciskOK) == LOW)
    {
      pozRefMin = bazowanie(min);
      delay(500);
      pozRefMax = bazowanie(max);
      lcd.clear();
      lcd.print("Baza 1:");
      lcd.setCursor(0, 1);
      lcd.print(pozRefMin);
      lcd.setCursor(4, 1);
      lcd.print(pozRefMax);
      delay(1000);
      baza = true;
    }
  }
  //lcd.clear();
  //exit(0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wcisnij OK");
  lcd.setCursor(0, 1);
  lcd.print("aby uruchomic");
  while (digitalRead(przyciskOK) == HIGH)
  {
      /* code */
  }
  
  if (digitalRead(przyciskOK) == LOW)
  {
    exit(0);
  }
}
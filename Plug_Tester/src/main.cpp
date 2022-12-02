#include <Arduino.h>
#include <Wire.h>   //biblioteka Wires, potrzebna do prawidłowego kompilowania programu (?)

#define IOpin0 10   //definicja pinów wejściowo-wyjściowych - podpięcie pod piny wtyczki
#define IOpin1 11
#define IOpin2 12
#define LED12 7     //definicja pinów pod diody sygnalizacyjne
#define LED23 6
#define LED31 5
#define LEDTest 13

bool result;
bool testResult;

int LED12stat = LOW;
int LED23stat = LOW;
int LED31stat = LOW;
int LEDTeststat = LOW;


void setup() {
  pinMode(IOpin0, INPUT_PULLUP);      //wstępnie, wszystkie piny jako input
  pinMode(IOpin1, INPUT_PULLUP);
  pinMode(IOpin2, INPUT_PULLUP);
  pinMode(LED12, OUTPUT);             //setup LED-pinów jako wyjścia
  pinMode(LED23, OUTPUT);
  pinMode(LED31, OUTPUT);
  pinMode(LEDTest, OUTPUT);
  digitalWrite(LED12, LED12stat);           //domyślnie wyłączenie wszystkich diodek
  digitalWrite(LED23, LED23stat);
  digitalWrite(LED31, LED31stat);
  digitalWrite(LEDTest, LEDTeststat);
}

int test (int pin){
  pinMode(IOpin0, INPUT_PULLUP);      //wstępnie, wszystkie piny jako input
  pinMode(IOpin1, INPUT_PULLUP);
  pinMode(IOpin2, INPUT_PULLUP);

  switch (pin)
  {
    case 0:
    pinMode(IOpin0, OUTPUT);            //ustawienie pierwszego pinu jako wyjście sygnału, pozostałe piny jako wejścia do nasłuchu sygnału
    digitalWrite(IOpin0, LOW);         //ustawienie stanu niskiego na pinie 0

    if (digitalRead(IOpin1) == LOW)
      {
        LED12stat = HIGH;
      }
      else
      {
        LED12stat = LOW;
      }
    if (digitalRead(IOpin2) == LOW)
      {
        LED31stat = HIGH;
      }
      else
      {
        LED31stat = LOW;
      }
    break;

    case 1:
    pinMode(IOpin1, OUTPUT);                //ustawienie drugiego pinu jako wyjście sygnału, pozostałe piny jako wejścia do nasłuchu sygnału
    digitalWrite(IOpin1, LOW);              //ustawienie stanu niskiego na pinie 1

    if (digitalRead(IOpin0) == LOW)
      {
        LED12stat = HIGH;
      }
      else
      {
        LED12stat = LOW;
      }
    if (digitalRead(IOpin2) == LOW)
    {
      LED23stat = HIGH;
    }
      else
      {
        LED23stat = LOW;
      }
    break;
    
    case 2:
    pinMode(IOpin2, OUTPUT);                //ustawienie trzeciego pinu jako wyjście sygnału, pozostałe piny jako wejścia do nasłuchu sygnału
    digitalWrite(IOpin2, LOW);              //ustawienie stanu niskiego na pinie 2

    if (digitalRead(IOpin0) == LOW)
      {
        LED31stat = HIGH;
      }
      else
      {
        LED31stat = LOW;
      }
    if (digitalRead(IOpin1) == LOW)
      {
        LED23stat = HIGH;
      }
      else
      {
        LED23stat = LOW;
      }
    break;
  }
  digitalWrite(LED12, LED12stat);
  digitalWrite(LED23, LED23stat);
  digitalWrite(LED31, LED31stat);
    if (LED12stat == HIGH || LED23stat == HIGH || LED31stat == HIGH)
      {
        digitalWrite(LEDTest, LOW);
      }
      else
      {
        digitalWrite(LEDTest, HIGH);
      }
  return result;
}

void loop() {
  for (size_t i = 0; i < 3; i++)
  {
    testResult = test(i);
    if (i == 2)
    {
      i = 0;
    }
  }
}
#include <Arduino.h>
#include <Wire.h>   //biblioteka Wires, potrzebna do prawidłowego kompilowania programu (?)

#define IOpin0 10   //definicja pinów wejściowo-wyjściowych - podpięcie pod piny wtyczki
#define IOpin1 11
#define IOpin2 12
// #define TestPin1 4
// #define TestPin2 3
// #define TestLed 5
#define LED12 7     //definicja pinów pod diody sygnalizacyjne
#define LED23 6
#define LED31 5

int Con12 = 0;      //zmienne do przechowywania statusu sygnalu na pinach
int Con23 = 0;
int Con31 = 0;


void setup() {
  pinMode(IOpin0, INPUT_PULLUP);      //wstępnie, wszystkie piny jako input
  pinMode(IOpin1, INPUT_PULLUP);
  pinMode(IOpin2, INPUT_PULLUP);
  // pinMode(TestPin1, INPUT_PULLUP);
  // pinMode(TestPin2, OUTPUT);
  pinMode(LED12, OUTPUT);             //setup LED-pinów jako wyjścia
  pinMode(LED23, OUTPUT);
  pinMode(LED31, OUTPUT);
  //pinMode(TestLed, OUTPUT);
  digitalWrite(LED12, LOW);           //domyślnie wyłączenie wszystkich diodek
  digitalWrite(LED23, LOW);
  digitalWrite(LED31, LOW);
  //digitalWrite(TestLed, LOW);
  //digitalWrite(TestPin2, LOW);
}

void loop() {
  pinMode(IOpin0, OUTPUT);            //ustawienie pierwszego pinu jako wyjście sygnału
  pinMode(IOpin1, INPUT_PULLUP);      //ustawienie pozostałych pinów jako wejścia do nasłuchu sygnału
  pinMode(IOpin2, INPUT_PULLUP);
  digitalWrite(IOpin0, LOW);         //ustawienie stanu wysokiego na pinie 0
  
  if (digitalRead(IOpin1) == LOW)
  {
    digitalWrite(LED12, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(LED12, LOW);
  }
  if (digitalRead(IOpin2) == LOW)
  {
    digitalWrite(LED31, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(LED31, LOW);
  }

  // if (digitalRead(TestPin1) == LOW)
  // {
  //   digitalWrite(TestLed, HIGH);
  //   delay(1000);
  // }
  //   digitalWrite(TestLed, LOW);
  
}
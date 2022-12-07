#include <Arduino.h>
#include <Wire.h>

#define LEDzielony 8
#define LEDczerwony 9
#define LEDniebieski 10
#define przekaznik 11
#define buttonPIN 12

bool standbyON;
bool heatON;
bool cooldownON;
uint8_t button;
uint8_t button_prev;


void setup() {
  pinMode(LEDzielony, OUTPUT);
  pinMode(LEDczerwony, OUTPUT);
  pinMode(LEDniebieski, OUTPUT);
  pinMode(przekaznik, OUTPUT);
  pinMode(buttonPIN, INPUT_PULLUP);

  digitalWrite(LEDzielony, HIGH);
  digitalWrite(LEDczerwony, HIGH);    //dla RGB ze wspolną anodą (+), dla stanu HIGH diody nie świecą
  digitalWrite(LEDniebieski, HIGH);
  digitalWrite(przekaznik, HIGH);     //dla przekaźnika z załączaniem do GND, dla stanu HIGH przekaźnij nie jest załączony

  button_prev = digitalRead(buttonPIN);

}

void loop() {
  button = digitalRead(buttonPIN);
  //digitalWrite(LEDzielony, LOW);
  if (button == LOW && button_prev == HIGH)
  {
    standbyON = LOW;
    digitalWrite(LEDzielony, standbyON);
    button_prev = digitalRead(buttonPIN);
  }
  if (button == LOW && button_prev == HIGH && standbyON == LOW)
  {
    standbyON = HIGH;
    digitalWrite(LEDzielony, standbyON);
    button_prev = digitalRead(buttonPIN);
  }
  
}
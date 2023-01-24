#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
unsigned long current_time = 0;
unsigned long previous_time = 0;
unsigned long start_time = 0;
unsigned long counter_time = 75000UL;                 // czas do odliczenia w ms UL
int time_to_calc = counter_time / 1000;               // przeliczenie czasu do odliczenia z ms na sekundy
int time_to_display = 0;                              // zmienna do przechowywania wartości wyświetlanej na wyświetlaczu
bool trigger = true;                                  // zmienna uruchamiająca odliczanie

void setup() {
  // #ifndef __AVR_ATtiny85__
  // Serial.begin(9600);
  // Serial.println("7 Segment Backpack Test");
  // #endif
  matrix.begin(0x70);                                 // ustawienie adresu wyświetlacza, wartość domyślna 0x70
  matrix.blinkRate(0);                                // ustawienie migania wyświetlacza, domyślnie 0 - brak migania
  matrix.setBrightness(0);                            // ustawienie jasności wyświetlacza, domyślnie 0 - minimum, 15 - max
}

int display_time (int time) {
  return time / 60 * 100 + time % 60;                 // przeliczenie sekund na wartość do wyświetlenia na ekranie, minuty i sekundy
}

void loop() {
  matrix.blinkRate(2);
  matrix.drawColon(true);
  matrix.writeDisplay();
  delay(2000);
  while (trigger == true)
  {
    matrix.blinkRate(0);
    matrix.drawColon(false);
    // time_to_display = time_to_calc / 60 * 100 + time_to_calc % 60;
    matrix.print(display_time(time_to_calc), DEC);
    matrix.writeDisplay();
    delay(1000);
    // current_time = millis();
    start_time = millis();
    previous_time = start_time;
    while (start_time + counter_time > millis())
    {
      // matrix.writeDigitNum(1, counter_time / 60000UL, false);
      // matrix.writeDisplay();
      if (millis() - previous_time >= 1000UL)
      {
        previous_time = millis();
        time_to_calc -= 1;
        // time_to_display = time_to_calc / 60 * 100 + time_to_calc % 60;
        time_to_display = display_time(time_to_calc);
        matrix.print(time_to_display, DEC);
        matrix.writeDisplay();
      }
      // current_time = millis();
    }
    trigger = false;
  }
  matrix.print(0000);
  matrix.drawColon(true);
  matrix.blinkRate(2);
  matrix.writeDisplay();
}
  

  // try to print a number thats too long
  // matrix.print(10000, DEC);
  // matrix.writeDisplay();
  // delay(1000);
  // matrix.clear();
  // matrix.writeDisplay();
  // delay(500);

  // print a hex number
  // matrix.print(0xBEEF, HEX);
  // matrix.writeDisplay();
  // delay(1000);
  // matrix.clear();
  // matrix.writeDisplay();
  // delay(500);

  // print a floating point 
  // matrix.print(12.34);
  // matrix.writeDisplay();
  // delay(1000);
  // matrix.clear();
  // matrix.writeDisplay();
  // delay(500);

  // draw dots
  // for (int i = 0; i < 10; i++)
  // {
  //   matrix.writeDigitNum(0, i, false);
  //   matrix.writeDigitNum(2, i, true);
  //   matrix.drawColon(true);
  //   matrix.writeDisplay();
  //   delay(1000);
  //   matrix.drawColon(false);
  //   matrix.writeDigitNum(2, i, true);
  //   matrix.writeDisplay();
  //   delay(1000);
  // }
  // matrix.clear();
  // matrix.writeDisplay();
  // delay(1000);
  

  // print with print/println
  // for (uint16_t counter = 0; counter < 999; counter++) {
  //   matrix.println(counter);
  //   matrix.writeDisplay();
  //   delay(10);
  // }

  /*
  uint16_t blinkcounter = 0;
  boolean drawDots = false;
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000), drawDots);
    matrix.writeDigitNum(1, (counter / 100) % 10, drawDots);
    matrix.drawColon(drawDots);
    matrix.writeDigitNum(3, (counter / 10) % 10, drawDots);
    matrix.writeDigitNum(4, counter % 10, drawDots);
   
    blinkcounter+=50;
    if (blinkcounter < 500) {
      drawDots = false;
    } else if (blinkcounter < 1000) {
      drawDots = true;
    } else {
      blinkcounter = 0;
    }
    matrix.writeDisplay();
    delay(10);
  }
  */
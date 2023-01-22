#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
unsigned long current_time = 0;
unsigned long start_time = 0;
int time_to_count = 60;
unsigned long last_read_time = 0;

void setup() {
  // #ifndef __AVR_ATtiny85__
  // Serial.begin(9600);
  // Serial.println("7 Segment Backpack Test");
  // #endif
  matrix.begin(0x70);
  matrix.blinkRate(0);
  matrix.setBrightness(0);
}

void loop() {
  matrix.blinkRate(2);
  matrix.drawColon(true);
  matrix.writeDisplay();
  delay(2000);
  bool i = true;
  current_time = millis();
  while (i == true)
  start_time = current_time;
  {
    while (start_time + time_to_count > current_time)
    {
      
    }
    
  }


  // try to print a number thats too long
  // matrix.print(1005, DEC);
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
}
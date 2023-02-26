// 13.02.2023 Update:
// V1.1
// 1. Extra condition added to heat and cooldown mode, the "if" checks also the current mode
// 2. Extra program to reset the arduino software, method is called after cooldown time end
// 3. Error program implemented. Basing on current behaviour of driver, the method is called after calling the reset.
//    That provide extra info if driver is stucked and need to be reset manually by pressing the button.
// 4. Some of the lines are moved to correct (better) positions to be executed when it is necessary.
// 5. All commented and not used anymore lines - are deleted.

// 18.02.2023 Update:
// V1.2
// 1. Software reset is disabled
// 2. Hardware + software reset is setup, A0 Pin as output to reset the driver
// 3. Reset works on Standby for each 30sec without enabling the program
// 4. Reset function is enabled after the cooldown time is gone.

// 24.02.2023 Update:
// V2.0
// 1. Function resetFunc is out
// 2. All polish names and comments are switched to english
// 3. Method for lighting the LEDs is add
// 4. A0 pin is out (previous used for hard reset)
// 5. Default times for counters are declared as const variables
// 6. One more mode is add, new set is: 0 - settings mode, 1 - Standby mode, 2 - Heating mode, 3 - Cooldown mode
// 7. Settings mode is use to setup the brightness of display. buttonPin close the setting when pressed -> switch mode to 1 (Standby)
// 8. A library for debouncing the button (ezButton) is add
// 9. Previous buttonPin is replaced with object "buttonPin" of ezButton class, pin attached (12) is not changed
// 10. If-s in main program loop are replaced by switch-case method
// 11. ADCread variable is out AnalogRead(A3) is directly put into the next line with mapping
// 12. The button method is out because of ezButton library use
// 13. Variable start_standby is gone.
// 14. defaultStandbyTime is gone.
// 15. New method for counting the delay is add (simple_delay())
// 16. All methods (standby, heat, cooldown) are changed basing on previous changes
// 17. When cooldown is finished, program switched to mode 1. The settings mode is avaliable only once when power on the device or hard reset

// 26.02.2023 Update:
// V2.01
// 1. LEDstat variable is now as global
// 2. Color LEDs are now declared with new names. Previous ones were the same as in Adafruit library for multi coloured displays


#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "ezButton.h"

#define LEDgreen 8
#define LEDred 9
#define LEDblue 10
#define RelayOut 11


Adafruit_7segment matrix = Adafruit_7segment();
ezButton buttonPIN(12);
//mode of the driver: 0 - settings, 1 - standby, 2 - heat, 3 - cooldown
int mode;
int timeToCalc;
int brightness = 0;
bool standbyON = false;
bool heatON = false;
bool cooldownON = false;
bool colonStatus = true;
bool delayFinished = false;
bool LED_stat = false;
const unsigned long defaultHeatTime = 600000UL;        //default time for Heating, 10m x 60s x 1000
const unsigned long defaultCooldownTime = 1800000UL;   //default time for Coolingdown, 30m x 60s x 1000
const unsigned long defaultWaitTime = 1000UL;          //default time for simple delay after entereing to new mode
const unsigned long blinkTime = 500UL;                 //default time for blinking
unsigned long start_heat = 0UL;
unsigned long start_cooldown = 0UL;
unsigned long previous_time = 0UL;


void setup()
{
  // setting the serial port, 9600 baud
  Serial.begin(9600);
  // setting the debounce time (in ms) for buttonPin
  buttonPIN.setDebounceTime(50);
  // default mode is Settings (0)
  mode = 0;
  // setting the Inputs and Outputs
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDred, OUTPUT);
  pinMode(LEDblue, OUTPUT);
  pinMode(RelayOut, OUTPUT);
  pinMode(A3, INPUT_PULLUP);
  // setting display adress, default is 0x70
  matrix.begin(0x70);
  // disabling the Relay for safety
  digitalWrite(RelayOut, HIGH);
  standbyON = false;
  heatON = false;
  cooldownON = false;
}


// method to light the LEDs
// output values for common anode (+), LOW in the LED ON, HIGH - OFF
void LED_lighting (int m)
{
  switch (m)
  {
  case 1:
    digitalWrite(LEDgreen, LOW);
    digitalWrite(LEDred, HIGH);
    digitalWrite(LEDblue, HIGH);
    break;
  
  case 2:
    digitalWrite(LEDgreen, HIGH);
    digitalWrite(LEDred, LOW);
    digitalWrite(LEDblue, HIGH);
    break;
  
  case 3:
    digitalWrite(LEDgreen, HIGH);
    digitalWrite(LEDred, HIGH);
    digitalWrite(LEDblue, LOW);
    break;
  
  default:
    digitalWrite(LEDgreen, HIGH);
    digitalWrite(LEDred, HIGH);
    digitalWrite(LEDblue, HIGH);
    break;
  }
}


// calculate seconds into value to display on 4 digit display mm:ss
int display_time (int t1)
{
  return int (t1 / 60 * 100 + t1 % 60);
}


// method for displaying values on LCD + colon blinking
void count_the_time (int t3)
{
  matrix.print(display_time(t3), DEC);
  colonStatus = !colonStatus;
  // IMPORTANT to make sure that colon is displayed, put the matrix.print line first, then matrix.drawColon, last: matrix.writeDisplay
  matrix.drawColon(colonStatus);
  matrix.writeDisplay();
}


bool simple_delay ()
{
  if (millis() - previous_time >= defaultWaitTime)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// a place where brightness of LCD display can be setup
void settings ()
{
  if (millis() - previous_time >= blinkTime)
  {
    previous_time = millis();
    LED_stat = !LED_stat;
    digitalWrite(LEDgreen, LED_stat);
    digitalWrite(LEDred, LED_stat);
    digitalWrite(LEDblue, LED_stat);
  }
  brightness = map((analogRead(A3)), 5, 1020, 0, 15);
  matrix.blinkRate(2);
  matrix.print(8888, DEC);
  matrix.setBrightness(brightness);
  matrix.drawColon(true);
  matrix.writeDisplay();
  if (buttonPIN.isPressed())
  {
    mode = 1;
    matrix.blinkRate(0);
    matrix.clear();
    matrix.writeDisplay();
  }
}


void standby()
{
  if (standbyON == false)
  {
    previous_time = millis();
    LED_lighting(mode);
    matrix.drawColon(true);
    matrix.writeDisplay();
    standbyON = true;
  }
  if (delayFinished == false)
  {
    delayFinished = simple_delay();
  }
  if (buttonPIN.isPressed() && delayFinished == true)
  {
    mode = 2;
    standbyON = false;
    delayFinished = false;
  }
}


void heat()
{
  if (heatON == false)
  {
    previous_time = millis();
    start_heat = millis();
    digitalWrite(RelayOut, LOW);            //turning the relay out ON
    LED_lighting (mode);
    timeToCalc = defaultHeatTime / 1000UL;  //calculating the default time to seconds
    heatON = true;
  }
  if (delayFinished == false)
  {
    delayFinished = simple_delay();
  }
  if (delayFinished == true)
  {
    if (millis() - start_heat <= defaultHeatTime)        //checking the main time counter for heating, if false
    {
      if (millis() - previous_time >= 1000UL)             //checking the time for change the display
      {
        previous_time = millis();
        timeToCalc -= 1;
        count_the_time(timeToCalc);
      }
      if (buttonPIN.isPressed())                  //checking the Trigger button state
      {                                           //if button is pressed go to cooldown (mode3)
        heatON = false;
        delayFinished = false;
        mode = 3;
        matrix.print(0, DEC);
        matrix.writeDisplay();
      }
    }
    else if (millis() - start_heat > defaultHeatTime)   //checking the main time counter for heating, if true
    {                                                   //if time is gone go to cooldown (mode3)
      heatON = false;
      delayFinished = false;
      mode = 3;
      matrix.print(0, DEC);
      matrix.writeDisplay();
    }
  }
}

void cooldown()
{
  if (cooldownON == false)
  {
    previous_time = millis();
    start_cooldown = millis();
    digitalWrite(RelayOut, HIGH);             //turning the relay out OFF
    LED_lighting (mode);
    timeToCalc = defaultCooldownTime / 1000UL;  //calculating the default time to seconds
    cooldownON = true;
  }
  if (delayFinished == false)
  {
    delayFinished = simple_delay();
  }
  if (delayFinished == true)
  {
    if (millis() - start_cooldown <= defaultCooldownTime)       //checking the main time counter for cooldown, if false
    {
      if (millis() - previous_time >= 1000UL)
      {
        previous_time = millis();
        timeToCalc -= 1;
        count_the_time(timeToCalc);
      }
    }
    else if (millis() - start_cooldown > defaultCooldownTime)  //checking the main time counter for cooldown, if true
    {
      cooldownON = false;
      delayFinished = false;
      mode = 1;
      matrix.clear();
      matrix.writeDisplay();
    }
  }
}

void loop() {
  buttonPIN.loop();
  switch (mode)
  {
  case 0:
    settings();
    break;
  case 1:
    standby();
    break;
  case 2:
    heat();
    break;
  case 3:
    cooldown();
    break;
  
  default:
    settings();
    break;
  }
}
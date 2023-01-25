#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"

#define LEDzielony 8
#define LEDczerwony 9
#define LEDniebieski 10
#define przekaznik 11
#define buttonPIN 12


Adafruit_7segment matrix = Adafruit_7segment();
int mode = 0;                         //mode(tryb) przyjmuje wartości: 0-dla standby, 1-dla heat, 2-dla cooldown
int time_to_calc;
bool standbyON = false;
bool heatON = false;
bool cooldownON = false;
bool colon_status = true;
unsigned long defaultHeatTime = 60000UL;        //domyślny czas dla grzania, finalnie wpisać 600000
unsigned long defaultCooldownTime = 180000UL;   //domyślny czas dla studzenia, finalnie wpisać 1800000
unsigned long previous_time = 0;
unsigned long start_heat = 0;
unsigned long start_cooldown = 0;


void setup()
{
  pinMode(LEDzielony, OUTPUT);
  pinMode(LEDczerwony, OUTPUT);
  pinMode(LEDniebieski, OUTPUT);
  pinMode(przekaznik, OUTPUT);
  pinMode(buttonPIN, INPUT_PULLUP);

  digitalWrite(LEDzielony, HIGH);
  digitalWrite(LEDczerwony, HIGH);    //dla RGB ze wspolną anodą (+), dla stanu HIGH diody nie świecą
  digitalWrite(LEDniebieski, HIGH);
  digitalWrite(przekaznik, HIGH);     //dla przekaźnika z załączaniem do GND, dla stanu HIGH przekaźnik jest wyłączony

  matrix.begin(0x70);                 // ustawienie adresu wyświetlacza, wartość domyślna 0x70
  matrix.blinkRate(0);                // ustawienie migania wyświetlacza, domyślnie 0 - brak migania
  matrix.setBrightness(0);            // ustawienie jasności wyświetlacza, domyślnie 0 - minimum, 15 - max

  mode = 0;
}

bool butt()
{
  bool buttonResult;
  while (digitalRead(buttonPIN) == LOW)
  { }
  delay(100);
  return buttonResult = true;
}

int display_time (int t1) {
  return int (t1 / 60 * 100 + t1 % 60);   // przeliczenie sekund na wartość do wyświetlenia na ekranie, minuty i sekundy
}


// metoda odejmująca sekundę i wyświetlająca wartość na wyświetlaczu
void count_the_time (int t3) {
  matrix.print(display_time(t3), DEC);
  colon_status = !colon_status;
  matrix.drawColon(colon_status);
  matrix.writeDisplay();
}

void standby()
{
  if (standbyON == false)
  {
    digitalWrite(przekaznik, HIGH);     //profilaktyczne wyłączenie przekaźnika
    digitalWrite(LEDczerwony, HIGH);    //
    digitalWrite(LEDniebieski, HIGH);   //wyłączenie diodek czerwonej i niebieskiej
    digitalWrite(LEDzielony, LOW);      //załączenie diody zielonej
    matrix.blinkRate(2);                // ustawienie migania na 1Hz
    colon_status = true;
    matrix.drawColon(colon_status);     // uruchomienie dwukropka
    matrix.writeDisplay();
    standbyON = true;
    heatON = false;
    cooldownON = false;
    delay(2000);
  }
  // Ważna uwaga, aby dwukropek był wyświetlony razem z wartością cyfrową
  // konieczne jest ustawienie NAJPIERW metody "print", a następnie "drawColon"
  time_to_calc = defaultHeatTime / 1000;
  matrix.print((display_time(time_to_calc)), DEC);
  matrix.drawColon(true);             // uruchomienie dwukropka
  matrix.writeDisplay();              // załączneie zmian w wyświetlaczu
  if (digitalRead(buttonPIN) == LOW)
  {
    if (butt() == true)
    {
      standbyON = false;
      cooldownON = false;
      mode = 1;
    }
  }
}

void heat()
{
  if (heatON == false)
  {
    digitalWrite(przekaznik, LOW);      //załączenie przekaźnika
    digitalWrite(LEDczerwony, LOW);     //załączenie diody czerwonej
    digitalWrite(LEDniebieski, HIGH);   //
    digitalWrite(LEDzielony, HIGH);     //wyłączenie diodek niebieskiej i zielonej
    start_heat = millis();
    previous_time = start_heat;
    heatON = true;
    colon_status = false;
    // time_to_calc = 600;
    matrix.blinkRate(0);
    // matrix.print(display_time(time_to_calc), DEC);
    // matrix.drawColon(colon_status);
    matrix.writeDisplay();
    delay(1000);
  }
  if (heatON == true)
  {
    if ((start_heat + defaultHeatTime) > millis())   //sprawdzenie, czy upłynął już domyślny czas grzania
    {
      if (millis() - previous_time >= 1000UL)
      {
        previous_time = millis();
        time_to_calc -= 1;
        count_the_time(time_to_calc);
      }
      if (digitalRead(buttonPIN) == LOW)                  //jeżeli nie, możemy wywołać zakończenie programu oraz przejście
      {                                                   //do podprogramu studzenia
        if (butt() == true)                               //taki zabieg można zrobić tylko raz przed upływem domyślnego czasu grzania
        {
          heatON = false;
          mode = 2;
          matrix.print(0, DEC);
          matrix.writeDisplay();
        }
      }
    }
    if ((start_heat + defaultHeatTime) <= millis())   //sprawdzenie, czy upłynął już domyślny czas grzania
    {
      heatON = false;
      mode = 2;                                           //jeżeli tak, przejdź od razu do podprogramu studzenia
      matrix.print(0, DEC);
      matrix.writeDisplay();
    }
  }
}

void cooldown()
{
  if (cooldownON == false)              //sprawdzenie stanu dla podprogramu studzenia, domyślnie jest false
  {
    digitalWrite(przekaznik, HIGH);     //wyłączenie przekaźnika
    digitalWrite(LEDczerwony, HIGH);    //wyłączenie diody czerwonej
    digitalWrite(LEDniebieski, LOW);    //załączenie diody niebieskiej
    digitalWrite(LEDzielony, HIGH);     //wyłączenie diody zielonej
    start_cooldown = millis();
    previous_time = start_cooldown;
    cooldownON = true;                  //załączenie stanu studzenia na true
    colon_status = false;
    time_to_calc = defaultCooldownTime / 1000;
    matrix.print(display_time(time_to_calc), DEC);
    matrix.drawColon(colon_status);
    matrix.writeDisplay();
  }
  if (cooldownON == true)
  {
    if ((start_cooldown + defaultCooldownTime) > millis())   //sprawdzenie, czy upłynął już domyślny czas studzenia
    {
      if (millis() - previous_time >= 1000UL)
      {
        previous_time = millis();
        time_to_calc -= 1;
        count_the_time(time_to_calc);
      }
      mode = 2;                                              //jeżeli nie minął, pozostań w trybie 2-cooldown
    }
    if ((start_cooldown + defaultCooldownTime) <= millis())  //sprawdzenie, czy upłynął już domyślny czas studzenia
    {
      matrix.print(0, DEC);
      matrix.writeDisplay();
      cooldownON = false;
      mode = 0;                                                    //jeżeli czas upłynął, przełącz na tryb 0-standby
    }
  }
}

void loop() {
  if (mode == 0)
  {
    standby();
  }
  if (mode == 1)
  {
    heat();
  }
  if (mode == 2)
  {
    cooldown();
  }
}
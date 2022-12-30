#include <Arduino.h>
#include <Wire.h>

#define LEDzielony 8
#define LEDczerwony 9
#define LEDniebieski 10
#define przekaznik 11
#define buttonPIN 12

int mode = 0;                         //mode(tryb) przyjmuje wartości: 0-dla standby, 1-dla heat, 2-dla cooldown
int buttonState;
int lastButtonState = HIGH;
bool standbyON = false;
bool heatON = false;
bool cooldownON = false;
unsigned long defaultHeatTime = 600000UL;        //domyślny czas dla grzania, finalnie wpisać 600000
unsigned long defaultCooldownTime = 1800000UL;   //domyślny czas dla studzenia, finalnie wpisać 1800000
unsigned long czas_aktualny = 0;
unsigned long start_heat = 0;
unsigned long start_cooldown = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;


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

void standby()
{
  if (standbyON == false)
  {
    digitalWrite(przekaznik, HIGH);     //profilaktyczne wyłączenie przekaźnika
    digitalWrite(LEDczerwony, HIGH);    //
    digitalWrite(LEDniebieski, HIGH);   //wyłączenie diodek czerwonej i niebieskiej
    digitalWrite(LEDzielony, LOW);      //załączenie diody zielonej
    standbyON = true;
    heatON = false;
    cooldownON = false;
    delay(2000);
  }
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
    czas_aktualny = millis();
    start_heat = czas_aktualny;
    heatON = true;
    delay(2000);
  }
  if (heatON == true)
  {
    czas_aktualny = millis();
    if ((start_heat + defaultHeatTime) > czas_aktualny)   //sprawdzenie, czy upłynął już domyślny czas grzania
    {
      if (digitalRead(buttonPIN) == LOW)                  //jeżeli nie, możemy wywołać zakończenie programu oraz przejście
      {                                                   //do podprogramu studzenia
        if (butt() == true)                               //taki zabieg można zrobić tylko raz przed upływem domyślnego czasu grzania
        {
          heatON = false;
          mode = 2;
        }
      }
    }
    if ((start_heat + defaultHeatTime) <= czas_aktualny)   //sprawdzenie, czy upłynął już domyślny czas grzania
    {
      heatON = false;
      mode = 2;                                           //jeżeli tak, przejdź od razu do podprogramu studzenia
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
    czas_aktualny = millis();
    start_cooldown = czas_aktualny;
    cooldownON = true;                  //załączenie stanu studzenia na true
  }
  if (cooldownON == true)
  {
    czas_aktualny = millis();
    if ((start_cooldown + defaultCooldownTime) > czas_aktualny)   //sprawdzenie, czy upłynął już domyślny czas studzenia
    {
      mode = 2;                                                   //jeżeli nie minął, pozostań w trybie 2-cooldown
    }
    if ((start_cooldown + defaultCooldownTime) <= czas_aktualny)    //sprawdzenie, czy upłynął już domyślny czas studzenia
    {
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
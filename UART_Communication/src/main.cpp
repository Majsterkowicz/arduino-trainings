#include <Arduino.h>
#define przycisk 7
#define LED 13
int licznik = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Witaj użytkowniku");
  pinMode(przycisk,INPUT_PULLUP); //przycisk sterujący
  pinMode(LED, OUTPUT);  // definicja portu 13 jako LED
  digitalWrite(LED, LOW); // wyłączenie LED 
}

void loop() {
  delay(200);
  if (digitalRead(przycisk) == LOW)
  {
    Serial.println("OK");  //wyświetl napis "OK"
    while (digitalRead(przycisk) == LOW)
    {
    delay(1000); //odczekaj 1s
    }
  }
   else 
  {
    Serial.println("ALARM");  //wyświetl napis "ALARM"
    licznik = licznik + 1;
    Serial.print("Licznik alarmów:");
    Serial.println(licznik);
    while (digitalRead(przycisk) == HIGH)
    {
    digitalWrite(LED, HIGH);  // sekwencja migania diody
    delay(200); //odczekaj 200ms
    digitalWrite(LED, LOW);
    delay(200); //odczekaj 200ms
    }
  }
  // put your main code here, to run repeatedly:
}
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

void onInterrupt();

Adafruit_BNO055 bno = Adafruit_BNO055(55);

#define PIN 9

#define BIN1 10
#define BIN2 12

#define ENC1A 7
#define ENC1B 6

void setup()
{
  pinMode(PIN, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(ENC1A, INPUT);
  pinMode(ENC1B, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENC1A), onInterrupt, RISING);

  if (!bno.begin())
  {
    while (1)
    {
      digitalWrite(PIN, HIGH);
      delay(500);
      digitalWrite(PIN, LOW);
      delay(1000);
    }
  }

  bno.setExtCrystalUse(true);
}

void onInterrupt()
{
  digitalWrite(PIN, HIGH);
  delayMicroseconds(50);
  digitalWrite(PIN, LOW);
}

void loop()
{
  sensors_event_t event;
  bno.getEvent(&event);

  digitalWrite(BIN1, HIGH);
  analogWrite(BIN2, 255 - constrain((int)event.orientation.y * 5, 0, 255));

  // digitalWrite(PIN, HIGH);
  // delay(min(10 * abs((int)event.orientation.y), 500));

  // digitalWrite(PIN, LOW);
  // delay(min(10 * abs((int)event.orientation.y), 500));
}

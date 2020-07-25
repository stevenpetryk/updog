#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include "pins.h"
#include "motor.h"

void onMotorFault();
void onIMUError();

Motor aMotor = Motor(A_MOTOR_1, A_MOTOR_2, A_ENCODER_1, A_ENCODER_2);
Motor bMotor = Motor(B_MOTOR_1, B_MOTOR_2, B_ENCODER_1, B_ENCODER_2);

Adafruit_BNO055 orientationSensor = Adafruit_BNO055(55);

void setup()
{
  pinMode(DEBUG_LED, OUTPUT);

  pinMode(DRV_FAULT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DRV_FAULT), onMotorFault, FALLING);

  if (!orientationSensor.begin())
    onIMUError();

  orientationSensor.setExtCrystalUse(true);
}

void loop()
{
}

/**
 * The BNO055 failed to ACK at its I2C address.
 *
 * 3 short blinks separated by a pause.
 */
void onIMUError()
{
  while (1)
  {
    digitalWrite(DEBUG_LED, HIGH);
    delay(50);
    digitalWrite(DEBUG_LED, LOW);
    delay(50);
    digitalWrite(DEBUG_LED, HIGH);
    delay(50);
    digitalWrite(DEBUG_LED, LOW);
    delay(50);
    digitalWrite(DEBUG_LED, HIGH);
    delay(50);
    digitalWrite(DEBUG_LED, LOW);
    delay(1000);
  }
}

/**
 * The DRV8833 has encountered an overcurrent, overtemperature, or some other
 * issue.
 *
 * 2 short blinks separated by a pause.
 */
void onMotorFault()
{
  aMotor.stop();
  bMotor.stop();
  while (1)
  {
    digitalWrite(DEBUG_LED, HIGH);
    delay(50);
    digitalWrite(DEBUG_LED, LOW);
    delay(50);
    digitalWrite(DEBUG_LED, HIGH);
    delay(50);
    digitalWrite(DEBUG_LED, LOW);
    delay(1000);
  }
}

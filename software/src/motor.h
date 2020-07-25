#include <Arduino.h>
#include <Encoder.h>

class Motor
{
  uint8_t out1;
  uint8_t out2;
  Encoder encoder;

public:
  Motor(uint8_t out1, uint8_t out2, uint8_t enc1, uint8_t enc2) : encoder(enc1, enc2)
  {
    this->out1 = out1;
    this->out2 = out2;

    pinMode(out1, OUTPUT);
    pinMode(out2, OUTPUT);
  }

  void stop()
  {
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
  }
};

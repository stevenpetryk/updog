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

  /**
   * Set the signal to a value between -100 and 100.
   *
   * Positive is counterclockwise, negative is clockwise.
   */
  void setSignal(int8_t signal)
  {
    int offset = map(abs(signal), 0, 100, 0, 256);

    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);

    if (signal > 0)
      analogWrite(out2, offset);
    else
      analogWrite(out1, offset);
  }

  /**
   * Ceases all motor rotation.
   */
  void stop()
  {
    setSignal(0);
  }

  /**
   * Smoothly oscillates between largest negative speed and largest positive
   * speed.
   */
  void testRange()
  {
    for (int i = 0; i >= -100; i--)
    {
      setSignal(i);
      delay(10);
    }

    while (1)
    {
      for (int i = -100; i <= 100; i++)
      {
        setSignal(i);
        delay(10);
      }

      for (int i = 100; i >= -100; i--)
      {
        setSignal(i);
        delay(10);
      }
    }
  }
};

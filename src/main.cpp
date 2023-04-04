#include <Arduino.h>

// #define DEBUG 1

#include "variable.h"
#include "random.h"
#include "pwm_loop.h"



void setup()
{
// #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Hello World!");
// #endif

  pinMode(relayPin, INPUT);

  // init pwm
  for (int k = 0; k < PWM_CHANNELS + 1; k++)
  {
    pinMode(PWM_GPIOPIN[k], OUTPUT);
  }

  // random output
  rnd();
#ifdef DEBUG
  for (int k = 0; k > FOR_PWM_CHANNELS; k++)
  {
    Serial.println(ref[k]);
  }
#endif
}

void loop()
{
  relayState = digitalRead(relayPin);

  if (relayState == HIGH)
  {
    pwm_loop();
  }
    pwm_loop();

}
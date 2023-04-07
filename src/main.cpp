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
  for (int k = 0; k < FOR_PWM_CHANNELS - 1; k++)
  {
    pinMode(PWM_GPIOPIN[k], OUTPUT);
  }

#ifdef DEBUG
  for (int k = 0; k > FOR_PWM_CHANNELS; k++)
  {
    Serial.println(ref[k]);
  }
#endif
  time_relay = millis() + time_boucle + 10;
}

void loop()
{
  relayState = digitalRead(relayPin);
  if (relayState == HIGH && state_relay == false)
  {
    state_relay = true;
    time_relay = millis();
  }
  if (time_boucle > millis() - time_relay)
  {
    pwm_loop();
    state_fade_out = true;
  }
  if (time_boucle < millis() - time_relay && state_fade_out)
  {
    Serial.print("GO ");
    GO_fade_out();
    state_rnd = true;
  }
  if (time_boucle < millis() - time_relay && state_rnd)
  {
    rnd();
    for (int d = 0; d < FOR_PWM_CHANNELS; d++)
    {
      analogWrite(PWM_GPIOPIN[d], 0);
      delay(2);
    }
    state_relay = false;
  }

  // pwm_loop();
}
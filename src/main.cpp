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
  rnd();
}

void loop()
{
  curent_relayState = digitalRead(relayPin);
  if (curent_relayState == HIGH && relayState == LOW)
  {
    relayState = HIGH;
    state_front = false;
    time_relay = millis();
    // pwm_loop();
    GO_fade_in();
  }

  if (curent_relayState == LOW && relayState == HIGH)
  {
    // relayState = LOW;
    state_front = true;
  }

  if (state_front == true && state_relay == false)
  {
    // state_relay = true;
  }

  if (state_relay)
  {
    if (time_boucle > millis() - time_relay)
    {
      // pwm_loop();
      GO_on();
      state_fade_out = true;
    }
    // if (time_boucle < millis() - time_relay && state_fade_out)
    if (time_boucle < millis() - time_relay)
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
      state_front = false;
      relayState = LOW;
    }
  }

  // pwm_loop();
}
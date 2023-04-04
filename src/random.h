#ifndef random_h
#define random_h

#include "Arduino.h"
#include "variable.h"

void rnd()
{
    randomSeed(analogRead(0));

    for (int j = 0; j < FOR_PWM_CHANNELS; j++)
    {
        ref[j] = {FOR_PWM_CHANNELS};
    }
    int i = 0;

    boolean equals;

    // while (i != FOR_PWM_CHANNELS)
    while (i < FOR_PWM_CHANNELS)
    {
        ref[i] = random(FOR_PWM_CHANNELS);

        equals = false;
        for (int k = 0; k != i; k++)
        {
            if (ref[k] == ref[i])
            {
                equals = true;
            }
        }
        if (!equals)
        {
            i++;
        }
    }

    for (int k = 0; k < FOR_PWM_CHANNELS; k++)
    {
#ifdef DEBUG
        Serial.print(" ** result k ref[");
        Serial.print(k);
        Serial.print("] = ");
        Serial.print(ref[k], DEC);
        Serial.print(" -> PIN = ");
        Serial.println(PWM_GPIOPIN[k]);
#endif
    }
}

#endif
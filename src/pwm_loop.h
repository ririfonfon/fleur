#ifndef pwm_loop_h
#define pwm_loop_h

#include "Arduino.h"
#include "variable.h"
#include "math.h"

void pwm_loop()
{
    // bool fade_clock;
    long currentMillis = millis();

    if (cycle)
    {
        previousMillis = currentMillis;
        cycle = false;
    } // if (cycle)

    for (int d = 0; d < FOR_PWM_CHANNELS; d++)
    {
        if (d == 0)
        {
            if (!f_i[d] && !p[d])
            {
                f_i[d] = true;
#ifdef DEBUG
                Serial.print(" +++ f_i[");
                Serial.print(d);
                Serial.print("] = ");
                Serial.print(f_i[d]);
                Serial.print(" at ");
                Serial.println(currentMillis);
#endif
            } // if (!f_i[d] && !p[d])
        }
        else
        {
            if (!f_i[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)
            {
                f_i[d] = true;
#ifdef DEBUG
                Serial.print(" +++ f_i[");
                Serial.print(d);
                Serial.print("] = ");
                Serial.print(f_i[d]);
                Serial.print(" at ");
                Serial.println(currentMillis);
#endif
            } // if (!f_i[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)
        }

        if (f_i[d])
        {
            if (fade_in != 0)
            {
                // fade_clock = millis() % fade_in < 10000000;
                // if (fade_clock && f_i[d])
                if (f_i[d])
                {
                    value[d] += Channel_mod;
                }
                if (value[d] > High_value)
                {
                    value[d] = High_value;
                    f_i[d] = false;
                    p[d] = true;
                    currentp[d] = currentMillis;

#ifdef DEBUG
                    Serial.print("fade_in  currentp[");
                    Serial.print(d);
                    Serial.print("] at ");
                    Serial.println(currentp[d]);
#endif
                }
            } // if (fade_in > 0)
            else if (fade_in <= 0)
            {
                value[d] = High_value;
                f_i[d] = false;
                p[d] = true;
                currentp[d] = currentMillis;

#ifdef DEBUG
                Serial.print("in cut currentp[");
                Serial.print(d);
                Serial.print("] at ");
                Serial.println(currentp[d]);
#endif
            } // else if (fade_in <= 0)
        }     // if (f_i[d])

        if (!f_o[d] && !p[FOR_PWM_CHANNELS] && !n[d] && p[d] && (currentMillis - currentp[d]) > on)
        {
            f_o[d] = true;
#ifdef DEBUG
            Serial.print(" f_o[");
            Serial.print(d);
            Serial.print("] = ");
            Serial.print(f_o[d]);
            Serial.print(" at ");
            Serial.println(currentMillis);
#endif
        } //(!p[FOR_PWM_CHANNELS] && !n[d] && p[d] && currentMillis - currentp[d] > on)

        if (f_o[d])
        {
            if (fade_out != 0)
            {
                // fade_clock = millis() % fade_out < 10000000;
                // if (fade_clock && f_o[d])
                if (f_o[d])
                {
                    value[d] -= Channel_mod;
                }
                if (value[d] < Def_Low_value)
                {
                    value[d] = Def_Low_value;
                    f_o[d] = false;
                    n[d] = true;
                    currentp[d] = currentMillis;

#ifdef DEBUG
                    Serial.print("fade_out  currentp[");
                    Serial.print(d);
                    Serial.print("] at ");
                    Serial.println(currentp[d]);
#endif
                }
            } // if (fade_out != 0)
            else if (fade_out <= 0)
            {
                value[d] = Def_Low_value;
                f_o[d] = false;
                n[d] = true;
                currentp[d] = currentMillis;

#ifdef DEBUG
                Serial.print("out cut currentp[");
                Serial.print(d);
                Serial.print("] at ");
                Serial.println(currentp[d]);
#endif
            } // else if (fade_out <= 0)
        }     // if (f_i[d])

        if (!p[FOR_PWM_CHANNELS] && n[FOR_PWM_CHANNELS - 1])
        {
            p[FOR_PWM_CHANNELS] = true;
            currentp[FOR_PWM_CHANNELS] = currentMillis;
#ifdef DEBUG
            Serial.print("currentp[");
            Serial.print(FOR_PWM_CHANNELS);
            Serial.print("] at ");
            Serial.println(currentp[FOR_PWM_CHANNELS]);
#endif
        }

        if (p[FOR_PWM_CHANNELS] && (currentMillis - currentp[FOR_PWM_CHANNELS]) > off)
        {
            previousMillis = currentMillis;
            for (int q = 0; q < FOR_PWM_CHANNELS; q++)
            {
                p[q] = false;
                f_i[q] = false;
                f_o[q] = false;
                n[q] = false;
                p[FOR_PWM_CHANNELS] = false;
            }
            High_value -= Master_mod;
        } // if (p[FOR_PWM_CHANNELS] && currentMillis - currentp[FOR_PWM_CHANNELS] > off)
    }     // for (int d = 0; d < FOR_PWM_CHANNELS; d++)

    for (int d = 0; d < FOR_PWM_CHANNELS; d++)
    {

        analogWrite(PWM_GPIOPIN[d], value[ref[d]]);
        delay(2);
    } // for(int d=0; d>FOR_PWM_CHANNELS;d++)
}
void GO_fade_in()
{
    while (value[0] != High_value || value[1] != High_value || value[2] != High_value || value[3] != High_value)
    {
        for (int d = 0; d < FOR_PWM_CHANNELS; d++)
        {

            if (value[d] >= High_value)
            {
                High_value = Def_High_value;
                value[d] = High_value;
            }
            else
            {
                value[d] += 1;
            }
            analogWrite(PWM_GPIOPIN[d], value[ref[d]]);
            delay(2);
        }
    }

    for (int q = 0; q < FOR_PWM_CHANNELS; q++)
    {
        p[q] = false;
        f_i[q] = false;
        f_o[q] = false;
        n[q] = false;
        p[FOR_PWM_CHANNELS] = false;
    }
    state_fade_in = false;
    cycle = true;
    state_relay = true;
}

void GO_on()
{
   for (int d = 0; d < FOR_PWM_CHANNELS; d++)
        {
            analogWrite(PWM_GPIOPIN[d], High_value);
            delay(2);
        } 
}

void GO_fade_out()
{
    while (value[0] != 0 || value[1] != 0 || value[2] != 0 || value[3] != 0)
    {
        for (int d = 0; d < FOR_PWM_CHANNELS; d++)
        {

            if (value[d] <= 0)
            {
                value[d] = 0;
                High_value = Def_High_value;
            }
            else
            {
                value[d] -= 1;
            }
            analogWrite(PWM_GPIOPIN[d], value[ref[d]]);
            delay(2);
        }
    }

    for (int q = 0; q < FOR_PWM_CHANNELS; q++)
    {
        p[q] = false;
        f_i[q] = false;
        f_o[q] = false;
        n[q] = false;
        p[FOR_PWM_CHANNELS] = false;
    }
    state_fade_out = false;
    cycle = true;
}

#endif
#include <Arduino.h>

#define DEBUG 1

const int relayPin = 2;
const int led1 = 5;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;

int relayState = 0;
int out1led;
int out2led;
int out3led;
int out4led;

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Hello World!");
#endif

  pinMode(relayPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop()
{
  relayState = digitalRead(relayPin);

  if (relayState == HIGH)
  {
#ifdef DEBUG
    Serial.println("Relay on");
#endif
    out1led++;
    if (out1led > 255)
    {
      out1led = 0;
    }
    analogWrite(led1,out1led);
  }
}
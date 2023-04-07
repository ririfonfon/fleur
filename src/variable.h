#ifndef variable_h
#define variable_h

#define PWM_CHANNELS 5 //

const int relayPin = 2;

int relayState = 0;

uint8_t PWM_GPIOPIN[4] = {5, 9, 10, 11};

long previousMillis = 0;
bool cycle = true;

bool f_i[PWM_CHANNELS + 1] = {false};
bool f_o[PWM_CHANNELS + 1] = {false};
bool p[PWM_CHANNELS + 1] = {false};
bool n[PWM_CHANNELS + 1] = {false};
// unsigned long currentp[PWM_CHANNELS];
long currentp[PWM_CHANNELS];

// DEFO
uint8_t FOR_PWM_CHANNELS = 4; // Outputs
long fade_in = 1;             // Seconds
long fade_out = 1;            // Seconds
long decalage = 200;         // Milliseconds
long on = 10;               // Milliseconds
long off = 10;              // Milliseconds
uint8_t High_value = 255;      //

int value[PWM_CHANNELS + 1] = {0};

uint8_t ref[PWM_CHANNELS + 1] = {0};

bool state_fade_out = true;
bool state_rnd = true;

bool start = true;

#endif
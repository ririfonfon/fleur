#ifndef variable_h
#define variable_h

#define PWM_CHANNELS 5 //

const int relayPin = 2;

int curent_relayState = 0;
int relayState = 0;

uint8_t PWM_GPIOPIN[4] = {5, 9, 10, 11};

long previousMillis = 0;
bool cycle = true;

bool f_i[PWM_CHANNELS + 1] = {false};
bool f_o[PWM_CHANNELS + 1] = {false};
bool p[PWM_CHANNELS + 1] = {false};
bool n[PWM_CHANNELS + 1] = {false};
long currentp[PWM_CHANNELS];

// DEFO
uint8_t FOR_PWM_CHANNELS = 4; // Outputs
long fade_in = 1;             // Seconds
long fade_out = 1;            // Seconds
long decalage = 300;          // Milliseconds
long on = 10;                 // Milliseconds
long off = 10;                // Milliseconds
long time_boucle = 8000;     // Milliseconds
const uint8_t Def_High_value = 255;     //
const uint8_t Def_Low_value = 0;     //
uint8_t Channel_mod = 5;
uint8_t Master_mod = 0;

int value[PWM_CHANNELS + 1] = {0};

uint8_t ref[PWM_CHANNELS + 1] = {0};

bool state_fade_out = true;
bool state_fade_in = true;
bool state_rnd = true;
bool state_front = false;

bool start = true;
bool state_relay = false;
long time_relay;

uint8_t High_value = Def_High_value;     //
#endif
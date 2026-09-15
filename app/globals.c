// globals.c
#include "globals.h"

#include <stdbool.h>

//--------------------------------------
// Global variable definitions & initial values
//--------------------------------------
uint8_t error_code = 0x01;

Mode mode = DEFROST_MODE;

CompressorState compressor_state = COMPRSR_OFF;
FanState fan_state = FAN_OFF;
HeaterState heater_state = HEATER_OFF;

float FRZ_temp = 0.00f;
float FF_temp = 0.00f;
bool door_state = false;
float voltage = 0.00f;
uint32_t deforest_count = 0;
uint32_t lockout_count = 0;



float DEFROST_CUT_TEMP = 0.00f;
uint32_t DEFROST_TIME = 9000;
uint32_t LOCKOUT_TIME = 0;
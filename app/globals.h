// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>  
#include <stdint.h>     // for uint8_t
#include <stdbool.h>
//-------------------------------------------------
// Mode Enum
//-------------------------------------------------
typedef enum {
    ERROR_MODE = 0,
    DEFROST_MODE,
    ACTIVE_MODE
} Mode;

//-------------------------------------------------
// Compressor State Enum
//-------------------------------------------------
typedef enum {
    COMPRSR_LCKOUT = 0,
    COMPRSR_READY,
    COMPRSR_STARTING,
    COMPRSR_RUNNING,
    COMPRSR_SET_STABLE,
    COMPRSR_OFF
} CompressorState;

//-------------------------------------------------
// Fan State Enum
//-------------------------------------------------
typedef enum {
    FAN_OFF = 0 ,
    FAN_WAITING ,
    FAN_RUNNING,

} FanState;

//-------------------------------------------------
// Heater State Enum
//-------------------------------------------------
typedef enum {
    HEATER_OFF = 0,
    HEATER_ON
} HeaterState;

//-------------------------------------------------
// Global variables (extern only)
//-------------------------------------------------
extern uint8_t error_code;

extern Mode mode;
extern CompressorState compressor_state;
extern FanState fan_state;
extern HeaterState heater_state;

extern float FRZ_temp;
extern float FF_temp;
extern bool door_state;
extern float voltage;
extern uint32_t deforest_count;
extern uint32_t lockout_count;

//-------------------------------------------------
// User macros 
//-------------------------------------------------
extern float DEFROST_CUT_TEMP;
extern uint32_t DEFROST_TIME;
extern uint32_t LOCKOUT_TIME; 
#endif

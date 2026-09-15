#ifndef SVC_FAN_H_
#define SVC_FAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/ADC.h>
#include <app/Drivers/GLOBAL.h>
#include <app/Drivers/FM.h>
#include <app/Drivers/PWM.h>
#include <app/Drivers/GPIO.h>


#include <FreeRTOS.h>
#include "task.h"
#include <stdint.h>
#include <math.h>
#include <limits.h> 
#include <app/Drivers/PID.h>





void svc_fan_waiting(void);
void svc_fan_running(void);
void svc_fan_off(void);





// typedef struct {

//     float frzr_Setpoint_Temp[SET_POINT_COUNT];
//     uint32_t frzr_Setpoint_Resistnt[SET_POINT_COUNT];
//     uint32_t frzr_Setpoint_Voltage[SET_POINT_COUNT];
//     uint8_t frzr_Setpoint_UP_GAP_Resistnt[SET_POINT_COUNT];
//     uint8_t frzr_Setpoint_UP_GAP_Voltage[SET_POINT_COUNT];
//     uint8_t frzr_Setpoint_LOW_GAP_Resistnt[SET_POINT_COUNT];
//     uint8_t frzr_Setpoint_LOW_GAP_Voltage[SET_POINT_COUNT];

// } frzr_Value;


// typedef struct {

//     float* frzr_Setpoint_Temp;
//     uint32_t* frzr_Setpoint_Resistnt;
//     uint32_t* frzr_Setpoint_Voltage;
//     uint8_t* frzr_Setpoint_UP_GAP_Resistnt;
//     uint8_t* frzr_Setpoint_UP_GAP_Voltage;
//     uint8_t* frzr_Setpoint_LOW_GAP_Resistnt;
//     uint8_t* frzr_Setpoint_LOW_GAP_Voltage;

// } frzr_Value;
















#endif /* SVC_FAN_H_ */

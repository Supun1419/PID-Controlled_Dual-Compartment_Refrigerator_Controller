#ifndef SVC_CMPRSR_H_
#define SVC_CMPRSR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/ADC.h>
#include <app/Drivers/GLOBAL.h>
#include <app/Drivers/FM.h>

#include <FreeRTOS.h>
#include "task.h"
#include <stdint.h>
#include <math.h>
#include <limits.h> 
#include <app/Drivers/PID.h>










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





void svc_lockout(void);
void svc_ready(void);
void svc_starting(void);
void svc_running(void);
void svc_set_stable(void);
void svc_com_off(void);













#endif /* SVC_CMPRSR_H_ */

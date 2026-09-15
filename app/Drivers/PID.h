#ifndef FRDG_PID_H_
#define FRDG_PID_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/UART2.h>
#include <stdarg.h>
#include "GLOBAL.h"



typedef struct{
    int32_t error_sum;
    double u;
    int32_t prev_error;

} PID_Tripple_t;


PID_Tripple_t* pid_cal(double kp,double ki,double kd,int32_t error,int32_t error_sum,int32_t prev_error);









#endif /* FRDG_PID_H_ */

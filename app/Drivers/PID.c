#include "PID.h"





PID_Tripple_t* pid_cal(double kp,double ki,double kd,int32_t error,int32_t error_sum,int32_t prev_error){

    PID_Tripple_t *p = (PID_Tripple_t*) malloc(sizeof(PID_Tripple_t));


    p->error_sum = error_sum + error;

    p->u = kp*error + ki*p->error_sum + kd*(error - prev_error);

    p->prev_error = error;

    return p;

}

























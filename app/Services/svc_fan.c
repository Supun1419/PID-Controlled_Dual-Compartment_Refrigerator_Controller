
#include "svc_fan.h"



void svc_fan_waiting(void){


    set_PWM(FAN_OFF_DUTY, FAN_OFF_FREQ, pwm_handl[2]);

}

void svc_fan_running(void){

    PID_Tripple_t * f = pid_cal(ff_Kp, ff_Ki, ff_Kd, ff_err, ff_err_sum, ff_err_prev);
    ff_err_pid = f->u;
    ff_err_prev = f->prev_error;
    ff_err_sum = f->error_sum;
    pwm_duty = ff_err_pid*(FAN_MAX_DUTY-FAN_MIN_DUTY)/(FAN_ERR_MAX-FAN_ERR_MIN);
    if(pwm_duty>100){
        pwm_duty =  100;
    }

    fan_pwm_duty = (uint32_t)pwm_duty; 
    set_PWM(fan_pwm_duty, FAN_ON_FREQ, pwm_handl[2]);
    free(f);

}


void svc_fan_off(void){

    set_PWM(FAN_OFF_DUTY, FAN_OFF_FREQ, pwm_handl[2]);


}


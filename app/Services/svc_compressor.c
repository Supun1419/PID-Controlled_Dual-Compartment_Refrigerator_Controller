
#include "svc_compressor.h"
#include <stdint.h>
#include <machine/_stdint.h>
#include <limits.h>
#include "app/globals.h"  
// uint32_t lockout_count =0;

void svc_lockout(void){

    set_FM(CMPRSR_OFF, pwm_handl[0]);

    lockout_count++;
}






void svc_ready(void){


    set_FM(CMPRSR_OFF, pwm_handl[0]);

    lockout_count = 0;

}



void svc_starting(void){


    set_FM(CMPRSR_MIN_FM, pwm_handl[0]);

    starting_count++;

}




void svc_running(void){

    PID_Tripple_t *p = pid_cal(frzr_Kp,frzr_Ki,frzr_Kd,frzr_err,frzr_err_sum,frzr_err_prev);
    frzr_err_prev = p->prev_error;
    frzr_err_pid = p->u;
    frzr_err_sum = p->error_sum;
    frzr_err_stp = frzr_err_pid*(FRZR_F_MAX-FRZR_F_MIN)/(FRZR_ERR_MAX-FRZR_ERR_MIN);
    if(frzr_currnt_stp>frzr_err_stp){

        frzr_currnt_stp = frzr_currnt_stp - DICREMENT_STEP;
    }
    else if(frzr_currnt_stp<frzr_err_stp){

        frzr_currnt_stp = frzr_currnt_stp + INCREMENT_STEP;

    }
    frzr_currnt_stp = frzr_currnt_stp+50;

    if(frzr_currnt_stp<10){
        frzr_currnt_stp = 10;
    }
    else if(frzr_currnt_stp > 150){
        frzr_currnt_stp = 150;
    }

    set_FM(frzr_currnt_stp, pwm_handl[0]);
    free(p);

}
// svc_running(){

// kp,ki,kd,error,error_sum=global
// error_sum,u=pid_cal()
// global=error_sum

// er_step= u/umax*(fmax-fmin)
// if(crr_step>err_step){
//     current_step-=DICREMENT_STEP
// }
// ELSE IF(crr_step<err_step){
//     current_step+=InCREMENT_STEP
// }
// 1-100 +50
// 0< frq 10, 150< frq 150
// FM(cru_stp,ch)

// }

void svc_set_stable(void)
{
    set_stable_count++;
    set_FM(CMPRSR_MIN_SET_FM,pwm_handl[0]);
}


void svc_com_off(void){

    set_FM(CMPRSR_OFF,pwm_handl[0]);

}







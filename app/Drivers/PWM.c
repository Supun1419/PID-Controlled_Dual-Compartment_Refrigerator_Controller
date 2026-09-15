#include "PWM.h"






void PWM_setup(uint_least8_t idx0,uint_least8_t idx1,uint_least8_t idx2,uint_least8_t idx3){

    PWM_init();
    PWM_Params_init(&PWMparams);
    PWMparams.dutyUnits   = PWM_DUTY_FRACTION;
    PWMparams.dutyValue   = 1;
    PWMparams.periodUnits = PWM_PERIOD_HZ;
    PWMparams.periodValue = 100;
    PWM_idx[0]=idx0;
    PWM_idx[1]=idx1;
    PWM_idx[2]=idx2;
    PWM_idx[3]=idx3;

    for(uint8_t itr = 0; itr<PWM_NUMBER;itr++){
        pwm_handl[itr]=PWM_open(PWM_idx[itr], &PWMparams);
        if(pwm_handl[itr] == NULL){
            //Error
        }
        else{
            
            PWM_start(pwm_handl[itr]);
            PWM_setDuty(pwm_handl[itr], 0);


        }
    }


}






void set_PWM(uint32_t Duty, uint32_t Freq, PWM_Handle Pwm_Handl){


    PWM_setDutyAndPeriod(Pwm_Handl,((uint64_t)PWM_DUTY_FRACTION_MAX * Duty) / 100,Freq);


}











































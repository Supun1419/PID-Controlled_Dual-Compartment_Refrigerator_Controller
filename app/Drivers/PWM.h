#ifndef FRDG_PWM_H_
#define FRDG_PWM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/PWM.h>
#include "GLOBAL.h"

void frdg_PWM_init(uint_least8_t idx0,uint_least8_t idx1,uint_least8_t idx2,uint_least8_t idx3);
void set_PWM(uint32_t Duty, uint32_t Freq, PWM_Handle Pwm_Handl);


#endif /* FRDG_PWM_H_ */

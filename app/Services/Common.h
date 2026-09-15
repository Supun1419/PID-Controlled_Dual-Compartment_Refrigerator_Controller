#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/ADC.h>
#include <app/Drivers/GLOBAL.h>
#include <FreeRTOS.h>
#include "task.h"
#include <app/Drivers/PWM.h>
#include <stdint.h>
#include <math.h>
#include <limits.h> 
#include <app/Drivers/NVS.h>




#define COMPRSR_LCKOUT 1

uint8_t set_Point_Select(uint32_t slctr_vltg);
void setpoint_Updt(void);




#endif /* COMMON_H_ */

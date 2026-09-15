#ifndef FRDG_GPIO_H_
#define FRDG_GPIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include "GLOBAL.h"

bool gpio_Cllbck(uint_least8_t index);
void GPIO_Setup(uint_least8_t ip_idx,uint_least8_t op_idx);
void GPIO_Wrt(uint_least8_t index, unsigned int value);




// extern uint_least8_t adc_Id_Array[4];


#endif /* FRDG_GPIO_H_ */

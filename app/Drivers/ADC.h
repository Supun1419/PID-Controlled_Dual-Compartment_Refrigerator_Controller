#ifndef FRDG_ADC_H_
#define FRDG_ADC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include "GLOBAL.h"

#define MAX_ADC_VOLTAGE 3300000
#define ADC_READ_ERROR 3



// extern uint_least8_t adc_Id_Array[4];

void ADC_Setup(uint_least8_t idx0,uint_least8_t idx1,uint_least8_t idx2,uint_least8_t idx3);

uint16_t ADC_Read(uint8_t indx);
uint32_t ADC_Voltage_Read(uint16_t ADC_value);
uint8_t set_Point_Select(uint32_t slctr_vltg);


#endif /* FRDG_ADC_H_ */

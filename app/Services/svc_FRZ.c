#include <stdint.h>
#include "svc_FRZ.h"

float svc_FRZ_temp_read(){
    uint32_t adc = 0;
    adc = ADC_Read(0); // TODO: check
    // TODO: error handle out of bound
    return svc_FRZ_adc_to_temp(adc);
}


float svc_FRZ_adc_to_temp(uint32_t adc){
      
      return adc/1000.00 ;// TODO: add actual funtion

}
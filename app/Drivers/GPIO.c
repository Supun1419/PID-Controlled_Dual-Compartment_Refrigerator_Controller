#include "GPIO.h"


bool gpio_Cllbck(uint_least8_t index)
{   
    bool gpio_pin_value = GPIO_read(index);
    return gpio_pin_value;
}

void GPIO_Setup(uint_least8_t ip_idx,uint_least8_t op_idx){
        
    out_p_idx = op_idx;
    in_p_idx = ip_idx;

    GPIO_init();
    GPIO_setConfig(ip_idx, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setConfig(op_idx, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    GPIO_setCallback(ip_idx, (void *)gpio_Cllbck);

    GPIO_enableInt(ip_idx);




}

void GPIO_Wrt(uint_least8_t index, unsigned int value){

    GPIO_write(index, value);
}






























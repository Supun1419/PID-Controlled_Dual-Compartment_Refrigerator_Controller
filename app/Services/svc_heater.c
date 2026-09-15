
#include "svc_heater.h"
#include "app/globals.h"

void svc_heater_on(void){

    GPIO_Wrt(out_p_idx, HEATER_ON);

}


void svc_heater_off(void){

    GPIO_Wrt(out_p_idx, HEATER_OFF);


}


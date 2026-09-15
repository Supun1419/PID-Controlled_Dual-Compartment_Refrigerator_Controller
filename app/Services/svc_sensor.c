#include <stdint.h>
#include "app/globals.h"
#include "svc_sensor.h"

void svc_read_sensor(){
    FRZ_temp = svc_FRZ_temp_read();
    //FF_temp = svc_FF_temp_read();
    //door_state = svc_door_state_read();
    //voltage = svc_voltage_read();

}
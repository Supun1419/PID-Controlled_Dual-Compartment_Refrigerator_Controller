#ifndef SVC_SENSOR_H
#define SVC_SENSOR_H

#include <stdint.h>
#include "app/globals.h"

// Function prototype
void svc_read_sensor(void);

// Sensor read function prototypes
// (These must match the functions you call in svc_read_sensor())

int16_t svc_FRZ_temp_read(void);
int16_t svc_FF_temp_read(void);
uint8_t svc_door_state_read(void);
uint16_t svc_voltage_read(void);

#endif // SVC_SENSOR_H

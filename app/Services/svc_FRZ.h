#ifndef SVC_FRZ_H
#define SVC_FRZ_H

#include <stdint.h>
#include "app/globals.h"
#include "app/Drivers/ADC.h"

// Public API: read freezer temperature (°C)
float svc_FRZ_temp_read(void);

// Convert ADC value to temperature
float svc_FRZ_adc_to_temp(uint32_t adc);

#endif // SVC_FRZ_TEMP_H

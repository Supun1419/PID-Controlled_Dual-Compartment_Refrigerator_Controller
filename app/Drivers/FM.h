#ifndef FRDG_FM_H_
#define FRDG_FM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/PWM.h>
#include "GLOBAL.h"

typedef PWM_Handle FM_Handle;

void set_FM(uint32_t Freq,FM_Handle Fm_Handl);


#endif /* FRDG_FM_H_ */

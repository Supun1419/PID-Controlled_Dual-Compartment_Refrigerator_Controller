#ifndef FRDG_NVS_H_
#define FRDG_NVS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include "GLOBAL.h"

void NVS_Setup(uint_least8_t idx);
void NVS_wrt(size_t offst,size_t byte_number, uint8_t* byte_buff);
void NVS_rd(size_t offst,size_t byte_number);

#endif /* FRDG_NVS_H_ */

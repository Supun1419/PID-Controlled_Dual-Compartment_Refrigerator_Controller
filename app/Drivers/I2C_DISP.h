#ifndef I2C_DISP_H_
#define I2C_DISP_H_

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ti/drivers/I2C.h>
#include <FreeRTOS.h>
#include "task.h"
#include <stdlib.h>
#include "ASCII_CONV.h"


extern I2C_Params i2cParams;
extern I2C_Handle i2c;
extern I2C_Transaction i2cTransaction;

extern uint_least8_t I2C_Pin_Idx;

void I2C_Set_def(uint_least8_t Pin_Idx);

void I2C_Setup(I2C_BitRate bit_Rate, uint_least16_t TgtAdrs, uint_least8_t Pin_Idx);

void I2C_Print_int(int32_t num);
void I2C_Print_string(const char *str);


// --- Generic macro to select correct version ---
#define I2C_Print(x) \
    _Generic((x), \
        int: I2C_Print_int, \
        const char*: I2C_Print_string, \
        char*: I2C_Print_string \
    )(x)


void I2C_trnscn(uint16_t arSze);



#endif /* I2C_DISP_H_ */

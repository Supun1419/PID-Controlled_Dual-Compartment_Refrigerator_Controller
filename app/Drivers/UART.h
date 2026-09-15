#ifndef FRDG_UART_H_
#define FRDG_UART_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/UART2.h>
#include <stdarg.h>
#include "GLOBAL.h"


typedef union uInt32_Value_struct
{
	
    uint32_t uInt32_Value;
	uint8_t uInt32_Value_buffer[sizeof(uint32_t)/sizeof(uint8_t)];
	
	
}uInt32_Value_t;

void callbackFxn(UART2_Handle handle, void *buffer, size_t count, void *userArg, int_fast16_t status);
void Frdg_UART_Init(uint_least8_t uart_Idx);
void Frdg_UART_Tx(void* UART_TX_BUFFER,uint8_t size_of_buffer);
void FILO(uint8_t* Buff, uint8_t buf_size);
uint8_t* Value_Seperator(uint32_t value);
void uart_Data_Pckt(uint32_t Top_reading, uint32_t Bottom_reading,uint8_t set_Point,uint8_t frzr_crnt_step,uint8_t ff_duty,uint32_t defrost_countr,uint32_t Defrost_stop_volt,uint8_t Heater_State, uint8_t Comprs_stat, uint8_t fan_stat, uint32_t Fan_start_voltage);




#endif /* FRDG_UART_H_ */

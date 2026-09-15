#include "UART.h"



UART2_Params uartParams;
UART2_Handle uart;
char read_Byte_Buf[1];
uint8_t temp_slctr;
char temp_buft;
uint8_t UART_TX_BUFF[100];
uint_least8_t uart_Id;
size_t bytesWritten = 0;
uint8_t Uart_Data_Pac[26];


void callbackFxn(UART2_Handle handle, void *buffer, size_t count, void *userArg, int_fast16_t status)
{ 

    temp_buft=*(char *)buffer;

    temp_selector = temp_buft - '0';

    UART2_read(uart,read_Byte_Buf,1,NULL);


}

void Frdg_UART_Init(uint_least8_t uart_Idx){

    UART2_Params_init(&uartParams);
    uartParams.readMode     = UART2_Mode_CALLBACK;
    uartParams.readCallback = callbackFxn;
    uartParams.baudRate     = 115200;
    uart_Id = uart_Idx;
    uart = UART2_open(uart_Id, &uartParams);
    UART2_read(uart,read_Byte_Buf,1,NULL);

}



void Frdg_UART_Tx(void* UART_TX_BUFFER,uint8_t size_of_buffer){

    UART2_write(uart, UART_TX_BUFFER, size_of_buffer, &bytesWritten);

}


void FILO(uint8_t* Buff, uint8_t buf_size){

    uint8_t lnth = 0;
    uint8_t temp = 0;

    lnth = (buf_size)>>1;

    for(uint8_t i =0; i < lnth; i++ ){

        temp = Buff[i];
        Buff[i]= Buff[buf_size - i - 1];
        Buff[buf_size - i - 1] = temp;

    }

}



uint8_t* Value_Seperator(uint32_t value){
    
    uint8_t *Value_buffer = (uint8_t*) malloc(4 * sizeof(uint8_t));  // allocate 4 bytes
    uInt32_Value_t Value_sep;
    Value_sep.uInt32_Value = value;
    FILO(Value_sep.uInt32_Value_buffer, sizeof(uint32_t));
    // Value_buffer = Value_sep.uInt32_Value_buffer;
    memcpy(Value_buffer, Value_sep.uInt32_Value_buffer, sizeof(uint32_t));
    // for(uint8_t itr = 0; itr< sizeof(uint32_t), itr++){
    //     Value_buffer[itr] = Value_sep.uInt32_Value_buffer[itr]
    // }

    return Value_buffer;
} 


void uart_Data_Pckt(uint32_t Top_reading, uint32_t Bottom_reading,uint8_t set_Point,uint8_t frzr_crnt_step,uint8_t ff_duty,uint32_t defrost_countr,uint32_t Defrost_stop_volt,uint8_t Heater_State, uint8_t Comprs_stat, uint8_t fan_stat, uint32_t Fan_start_voltage){

    uint8_t *Temp_Buff = Value_Seperator(Top_reading);
    memcpy(Uart_Data_Pac, Temp_Buff, 4);

    Temp_Buff = Value_Seperator(Bottom_reading);
    memcpy(Uart_Data_Pac + 4, Temp_Buff, 4);

    Uart_Data_Pac[8]=set_Point;
    Uart_Data_Pac[9]=frzr_crnt_step;
    Uart_Data_Pac[10]=ff_duty;

    Temp_Buff = Value_Seperator(defrost_countr);
    memcpy(Uart_Data_Pac + 11, Temp_Buff, 4);

    Temp_Buff = Value_Seperator(Defrost_stop_volt);
    memcpy(Uart_Data_Pac + 15, Temp_Buff, 4);

    Uart_Data_Pac[19]=Heater_State;
    Uart_Data_Pac[20]=Comprs_stat;
    Uart_Data_Pac[21]=fan_stat;

    Temp_Buff = Value_Seperator(Fan_start_voltage);
    memcpy(Uart_Data_Pac + 22, Temp_Buff, 4);


}


































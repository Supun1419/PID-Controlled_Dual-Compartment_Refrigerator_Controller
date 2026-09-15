#include "I2C_DISP.h"



I2C_Params i2cParams;
I2C_Handle i2c;
I2C_Transaction i2cTransaction;
uint8_t I2CtxBuffer[400];
uint8_t I2CrxBuffer[400];
char Print_Arr[400];
uint_least8_t I2C_Pin_Idx;

void I2C_Set_def(uint_least8_t Pin_Idx){

    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2cTransaction.writeBuf   = I2CtxBuffer;
    i2cTransaction.readBuf    = I2CrxBuffer;
    i2cTransaction.readCount  = 0;
    i2cTransaction.targetAddress = 0x28;
    I2C_Pin_Idx= Pin_Idx;



}


void I2C_Setup(I2C_BitRate bit_Rate, uint_least16_t TgtAdrs, uint_least8_t Pin_Idx){

    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = bit_Rate;
    i2cTransaction.writeBuf   = I2CtxBuffer;
    i2cTransaction.readBuf    = I2CrxBuffer;
    i2cTransaction.readCount  = 0;
    i2cTransaction.targetAddress = TgtAdrs;
    I2C_Pin_Idx= Pin_Idx;



}




void I2C_Print_int(int32_t num){
    uint16_t Array_Size_num;

    convert_to_char_array(num,Print_Arr);
    for(uint8_t itr =0; Print_Arr[itr]!=0;itr++){
        Array_Size_num = itr+1;

    }
    I2C_trnscn(Array_Size_num);



    
}

void I2C_Print_string(const char *str){
    uint16_t Array_Size_str;

    convert_to_char_array(str,Print_Arr);
    for(uint8_t itr =0; Print_Arr[itr]!=0;itr++){
        Array_Size_str = itr+1;

    }
    I2C_trnscn(Array_Size_str);




    
}

void I2C_trnscn(uint16_t arySze){

    memcpy(I2CtxBuffer, (void *)Print_Arr, arySze);
    i2cTransaction.writeCount = arySze;

    i2c = I2C_open(I2C_Pin_Idx, &i2cParams);

    I2C_transfer(i2c, &i2cTransaction);

    I2C_close(i2c);


}






















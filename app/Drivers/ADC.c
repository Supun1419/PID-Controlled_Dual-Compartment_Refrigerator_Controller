#include "ADC.h"





void ADC_Setup(uint_least8_t idx0,uint_least8_t idx1,uint_least8_t idx2,uint_least8_t idx3){

    ADC_init();
    ADC_Params_init(&params);
    adc_Id_Array[0]= idx0;
    adc_Id_Array[1]= idx1;
    adc_Id_Array[2]= idx2;
    adc_Id_Array[3]= idx3;


}

uint16_t ADC_Read(uint8_t indx){

    uint16_t raw_ADC_Value;
    uint16_t raw_ADC_Value_return;

    adc=ADC_open(adc_Id_Array[indx], &params);
    int_fast16_t adc_Convsn_stat = ADC_convert(adc, &raw_ADC_Value);
    if(adc_Convsn_stat==ADC_STATUS_SUCCESS){
        raw_ADC_Value_return = raw_ADC_Value;

    }
    else{
        raw_ADC_Value_return = 0;
    }
    return raw_ADC_Value_return;
}


uint32_t ADC_Voltage_Read(uint16_t ADC_value){

    uint32_t u_Volt_Value;
    u_Volt_Value = ADC_convertToMicroVolts(adc, ADC_value);

    ADC_close(adc);
    return u_Volt_Value;

}


// uint32_t* ADC_Mltpl_Read(uint8_t num_conversions,uint8_t start_id){

//     uint32_t* conv_array = malloc(num_conversions * sizeof(uint32_t));

//     for(uint8_t itr=0;itr<num_conversions;itr++){

//         conv_array[itr]=frdg_ADC_Single_Read(start_id+itr);
        
//     }
//     return conv_array;


// }


uint8_t set_Point_Select(uint32_t slctr_vltg){

    uint8_t slctr;

    if( 0 <= slctr_vltg && slctr_vltg < 314285 ){
        slctr=1;
    }
    else if( 314285 <= slctr_vltg && slctr_vltg < 628571 ){
        slctr=2;
    }
    else if( 628571 <= slctr_vltg && slctr_vltg < 942857 ){
        slctr=3;
    }
    else if( 942857 <= slctr_vltg && slctr_vltg < 1257142 ){
        slctr=4;
    }
    else if( 1257142 <= slctr_vltg && slctr_vltg < 1571428 ){
        slctr=5;
    }
    else if( 1571428 <= slctr_vltg && slctr_vltg < 1885714 ){
        slctr=6;
    }
    else if( 1885714 <= slctr_vltg && slctr_vltg < 2200000 ){
        slctr=7;
    }
    else if( 2200000 <= slctr_vltg && slctr_vltg < 2514286 ){
        slctr=8;
    }
    else{
        slctr=4;
    }


    if(slctr != 8){

        temp_selector = 4;

    }
    else{
        slctr=temp_selector;
    }


    return slctr;

}
































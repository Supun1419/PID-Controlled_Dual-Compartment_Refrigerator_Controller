#include "Common.h"

// uint8_t set_Point_Select(uint32_t slctr_vltg){

//     uint8_t slctr;

//     if( 0 <= slctr_vltg && slctr_vltg < 314285 ){
//         slctr=1;
//     }
//     else if( 314285 <= slctr_vltg && slctr_vltg < 628571 ){
//         slctr=2;
//     }
//     else if( 628571 <= slctr_vltg && slctr_vltg < 942857 ){
//         slctr=3;
//     }
//     else if( 942857 <= slctr_vltg && slctr_vltg < 1257142 ){
//         slctr=4;
//     }
//     else if( 1257142 <= slctr_vltg && slctr_vltg < 1571428 ){
//         slctr=5;
//     }
//     else if( 1571428 <= slctr_vltg && slctr_vltg < 1885714 ){
//         slctr=6;
//     }
//     else if( 1885714 <= slctr_vltg && slctr_vltg < 2200000 ){
//         slctr=7;
//     }
//     else if( 2200000 <= slctr_vltg && slctr_vltg < 2514286 ){
//         slctr=8;
//     }
//     else{
//         slctr=4;
//     }


//     if(slctr != 8){

//         temp_selector = 4;

//     }
//     else{
//         slctr=temp_selector;
//     }


//     return slctr;

// }





void setpoint_Updt(void){

    uint8_t strd_setpoint = NV_Memory[0];
    if(strd_setpoint != selector){
        NV_Memory[0]=selector;
        NVS_wrt(0,sizeof(NV_Memory),NV_Memory);
    }



}








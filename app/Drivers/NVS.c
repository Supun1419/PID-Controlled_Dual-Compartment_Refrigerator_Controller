#include "NVS.h"


NVS_Params nvsParams;
NVS_Handle nvsHandle;
uint_least8_t NVS_id;

void NVS_Setup(uint_least8_t idx){


    NVS_init();
    NVS_Params_init(&nvsParams);
    NVS_id = idx;


}


void NVS_wrt(size_t offst,size_t byte_number, uint8_t* byte_buff){
        
    memcpy(NVM_tx_buff, byte_buff, byte_number);

    nvsHandle = NVS_open(NVS_id, &nvsParams);
    NVS_write(nvsHandle, offst , (void *)NVM_tx_buff, byte_number,  NVS_WRITE_POST_VERIFY);

    // NVS_write(nvsHandle, offst , NVM_tx_buff, byte_number, NVS_WRITE_ERASE | NVS_WRITE_POST_VERIFY);
    NVS_close(nvsHandle);


}



void NVS_rd(size_t offst,size_t byte_number){

    nvsHandle = NVS_open(NVS_id, &nvsParams);
    NVS_read(nvsHandle, offst, (void *)NVM_rx_buff, byte_number);
    NVS_close(nvsHandle);


}

// void NV_Memory_Load(void){

//     NVS_rd(0, sizeof(NVM_rx_buff));
//     memcpy(NV_Memory, NVM_rx_buff, sizeof(NVM_rx_buff));


// }

// void setpoint_Updt(void){

//     uint8_t strd_setpoint = NV_Memory[0];
//     if(strd_setpoint != selector){
//         NV_Memory[0]=selector;
//         NVS_wrt(0,sizeof(NV_Memory),NV_Memory);
//     }



// }






















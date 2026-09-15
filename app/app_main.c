/******************************************************************************

@file  app_main.c

@brief This file contains the application main functionality

Group: WCS, BTS
Target Device: cc23xx

******************************************************************************

 Copyright (c) 2022-2025, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

******************************************************************************


*****************************************************************************/

//*****************************************************************************
//! Includes
//*****************************************************************************
#include "Drivers/GLOBAL.h"
#include "ti_ble_config.h"
#include "ti/ble/app_util/framework/bleapputil_api.h"
#include "ti/ble/app_util/menu/menu_module.h"
#include <app_main.h>
#include <FreeRTOS.h>
#include "task.h"
#include <stdint.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/ADC.h>
#include "ti_drivers_config.h"
#include <ti/drivers/PWM.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/NVS.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>  // for UINT32_MAX

#include "globals.h"
#include "app/Services/svc_sensor.h"


// Parameters that should be given as input to the BLEAppUtil_init function
BLEAppUtil_GeneralParams_t appMainParams =
{
    .taskPriority = 1,
    .taskStackSize = 1024,
    .profileRole = (BLEAppUtil_Profile_Roles_e)(HOST_CONFIG),
    .addressMode = DEFAULT_ADDRESS_MODE,
    .deviceNameAtt = attDeviceName,
    .pDeviceRandomAddress = pRandomAddress,
};

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG | CENTRAL_CFG ) )
BLEAppUtil_PeriCentParams_t appMainPeriCentParams =
{
#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG ) )
 .connParamUpdateDecision = DEFAULT_PARAM_UPDATE_REQ_DECISION,
#endif //#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG ) )

#ifdef GAP_BOND_MGR
 .gapBondParams = &gapBondParams
#endif //GAP_BOND_MGR
};
#else //observer || broadcaster
BLEAppUtil_PeriCentParams_t appMainPeriCentParams;
#endif //#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG | CENTRAL_CFG ) )
//---------------------------------------------start-------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GLOBAL VARIABLE
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNTIONS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t svc_main_init(void);
uint8_t svc_NVS_memory_Load(void);
uint8_t svc_read_sensors(void);


void mode_handler(void);
void operation_handler(void);

void svc_error_handler(void);
void svc_defrost_handler(void);
void svc_active_handler(void);

uint8_t svc_uart_handler(void);


void main_Task(void *pvParameters) 
{     


    error_code = svc_main_init(); // TODO:
    error_code = svc_NVS_memory_Load(); //TODO:

    while(1){

        svc_read_sensor();
        vTaskDelay(pdMS_TO_TICKS(100));
        //error_check();

        mode_handler();
        operation_handler();

        error_code = svc_uart_handler();
        vTaskDelay(pdMS_TO_TICKS(650));


    }

}

uint8_t svc_main_init(void){
    return 0x01; // TODO: init all thing, if there is error return the error code
}

uint8_t svc_NVS_memory_Load(void){
    return 0x01; // TODO: get all predefine variables from flash, if there is error return the error code
}


void mode_handler(void){


    switch(mode) 
    {
    case ERROR_MODE:
        // TODO error fix or not check and move to active or deforest
        svc_error_handler();
       
        break;

    case DEFROST_MODE:
        if(DEFROST_CUT_TEMP < FRZ_temp){
            mode = ACTIVE_MODE;
            compressor_state = COMPRSR_LCKOUT;
            fan_state = FAN_WAITING;
            heater_state = HEATER_OFF;

        }
        svc_defrost_handler();
        break;

    case ACTIVE_MODE:
        break;

    default:
        break;
    }

}

void svc_error_handler(void){
    // return NULL;

}

void svc_defrost_handler(void){
    // return NULL;
}

void svc_active_handler(void){
    if(DEFROST_TIME<deforest_count){
            compressor_state = COMPRSR_OFF;
            fan_state = FAN_OFF;
            heater_state = HEATER_ON;
    }
    switch(compressor_state) 
    {

    case COMPRSR_LCKOUT:
        if(LOCKOUT_TIME < lockout_count){
            compressor_state = COMPRSR_READY;
        }
        break;

    case COMPRSR_READY:
        break;

    case COMPRSR_STARTING:
        break;

    case COMPRSR_RUNNING:
        break;

    case COMPRSR_OFF:
        break;

    default:
        break;
    }

    switch(fan_state) 
    {

    case FAN_WAITING:
        break;

    case FAN_RUNNING:
        break;

    case FAN_OFF:
        break;

    default:
        break;
    }


    heater_state = HEATER_OFF;
    //return NULL;
}

uint8_t svc_uart_handler(){
    return 0x01; // TODO: handel the get&set and also notify, if there is error return the error code
}


void operation_handler(void){

    switch(compressor_state) 
    {

    case COMPRSR_LCKOUT:
        break;

    case COMPRSR_READY:
        break;

    case COMPRSR_STARTING:
        break;

    case COMPRSR_RUNNING:
        break;

    case COMPRSR_OFF:
        break;

    default:
        break;
    }

    switch(fan_state) 
    {

    case FAN_WAITING:
        break;

    case FAN_RUNNING:
        break;

    case FAN_OFF:
        break;

    default:
        break;
    }


    switch(heater_state) 
    {

    case HEATER_ON:
        break;

    case HEATER_OFF:
        break;

    default:
        break;
    }

}





/*********************************************************************
 * @fn      criticalErrorHandler
 *
 * @brief   Application task entry point
 *
 * @return  none
 */
void criticalErrorHandler(int32 errorCode , void* pInfo)
{
//    trace();
//
//#ifdef DEBUG_ERR_HANDLE
//
//    while (1);
//#else
//    SystemReset();
//#endif

}

/*********************************************************************
 * @fn      App_StackInitDone
 *
 * @brief   This function will be called when the BLE stack init is
 *          done.
 *          It should call the applications modules start functions.
 *
 * @return  none
 */
void App_StackInitDoneHandler(gapDeviceInitDoneEvent_t *deviceInitDoneData)
{
    bStatus_t status = SUCCESS;

    // Menu
    Menu_start();

    // Print the device ID address
    MenuModule_printf(APP_MENU_DEVICE_ADDRESS, 0, "BLE ID Address: "
                      MENU_MODULE_COLOR_BOLD MENU_MODULE_COLOR_GREEN "%s" MENU_MODULE_COLOR_RESET,
                      BLEAppUtil_convertBdAddr2Str(deviceInitDoneData->devAddr));

    if ( appMainParams.addressMode > ADDRMODE_RANDOM)
    {
      // Print the RP address
        MenuModule_printf(APP_MENU_DEVICE_RP_ADDRESS, 0,
                     "BLE RP Address: "
                     MENU_MODULE_COLOR_BOLD MENU_MODULE_COLOR_GREEN "%s" MENU_MODULE_COLOR_RESET,
                     BLEAppUtil_convertBdAddr2Str(GAP_GetDevAddress(FALSE)));
    }

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG | CENTRAL_CFG ) )
    status = DevInfo_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
    status = SimpleGatt_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
#endif

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG | CENTRAL_CFG ))  &&  defined(OAD_CFG)
    status =  OAD_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
#endif

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG ) )
    // Any device that accepts the establishment of a link using
    // any of the connection establishment procedures referred to
    // as being in the Peripheral role.
    // A device operating in the Peripheral role will be in the
    // Peripheral role in the Link Layer Connection state.
    status = Peripheral_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
#endif

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( BROADCASTER_CFG ) )
    // A device operating in the Broadcaster role is a device that
    // sends advertising events or periodic advertising events
    status = Broadcaster_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
#endif

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( CENTRAL_CFG ) )
    // A device that supports the Central role initiates the establishment
    // of an active physical link. A device operating in the Central role will
    // be in the Central role in the Link Layer Connection state.
    // A device operating in the Central role is referred to as a Central.
    status = Central_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
#endif

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( OBSERVER_CFG ) )
    // A device operating in the Observer role is a device that
    // receives advertising events or periodic advertising events
    status = Observer_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
#endif

#if defined( HOST_CONFIG ) && ( HOST_CONFIG & ( PERIPHERAL_CFG | CENTRAL_CFG ) )
    status = Connection_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
    status = Pairing_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }
    status = Data_start();
    if(status != SUCCESS)
    {
        // TODO: Call Error Handler
    }

#if defined (BLE_V41_FEATURES) && (BLE_V41_FEATURES & L2CAP_COC_CFG)
    /* L2CAP COC Init */
    status = L2CAPCOC_start();
    if ( status != SUCCESS )
    {
    // TODO: Call Error Handler
    }
#endif //(BLE_V41_FEATURES) && (BLE_V41_FEATURES & L2CAP_COC_CFG)

#endif
}

/*********************************************************************
 * @fn      appMain
 *
 * @brief   Application main function
 *
 * @return  none
 */
void appMain(void)
{
    // Call the BLEAppUtil module init function
    BLEAppUtil_init(&criticalErrorHandler, &App_StackInitDoneHandler,
                    &appMainParams, &appMainPeriCentParams);
}

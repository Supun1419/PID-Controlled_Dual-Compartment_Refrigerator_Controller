#ifndef FRDG_GLOBAL_H_
#define FRDG_GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/NVS.h>
#include <ti/drivers/GPIO.h>


#define SET_POINT_COUNT 7

#define LOWER_GAP 30000
#define UPPER_GAP -30000

#define STABLE_TIME 10
#define FRZR_F_MAX 150
#define FRZR_F_MIN 0
#define FRZR_ERR_MAX 1906495
#define FRZR_ERR_MIN 0
#define STEP_SIZE 1
#define DICREMENT_STEP 1
#define INCREMENT_STEP 1

#define FM_DUTY 50

#define FF_ERR_MAX 1906495
#define FF_ERR_MIN 0
#define CMPRSR_OFF 10
#define CMPRSR_MIN_FM 50
#define CMPRSR_MIN_SET_FM 50

#define FAN_OFF_DUTY 0
#define FAN_OFF_FREQ 0
#define FAN_MAX_DUTY 100
#define FAN_MIN_DUTY 0
#define FAN_ON_FREQ 100
#define FAN_ERR_MAX 1906495
#define FAN_ERR_MIN 0
#define PWM_NUMBER 4










#define FRZR_FUNC_OFFSET 0.0f
#define FRZR_TEMP_OFFSET 0.0f




extern uint_least8_t in_p_idx;
extern uint_least8_t out_p_idx;

extern uint16_t set_stable_count;
extern uint8_t starting_count;
extern uint8_t temp_selector;
extern uint32_t ADC0;
extern uint32_t ADC1;
extern uint32_t ADC2;
extern uint32_t ADC3;
extern uint32_t comprsr_pwm_freq;
extern uint32_t comprsr_pwm_duty;
extern uint32_t fan_pwm_duty;
extern uint32_t fan_pwm_freq;
// extern uint8_t compressor_state;
// extern uint16_t lockout_counter;
extern uint8_t start_counter;
extern uint8_t selector;
extern uint32_t frzr_setpoint_voltages[7];
extern int32_t frzr_err;
extern int32_t frzr_err_sum;
extern uint32_t frzr_temp;
extern double frzr_err_pid;
extern int32_t frzr_err_prev;
extern double frzr_Kp;
extern double frzr_Ki;
extern double frzr_Kd;
extern int32_t frzr_err_pid_int;
extern int32_t temp_err_pid_int;
extern int32_t max_err_pid_int;
extern int32_t frzr_err_stp;
extern int32_t frzr_currnt_stp;
extern uint8_t init_stbl_count;
// extern uint8_t fan_state;
extern uint32_t frzr_deadband;
extern bool gpio_val;





extern PWM_Params PWMparams;
extern uint_least8_t PWM_idx[PWM_NUMBER];
extern PWM_Handle pwm_handl[PWM_NUMBER];

extern uint8_t NV_Memory[100];
extern uint8_t NVM_tx_buff[100];
extern uint8_t NVM_rx_buff[100];
extern uint_least8_t gpio_idx;

extern int32_t ff_err;
extern uint32_t ff_temp;
extern int32_t ff_err_sum;
extern double ff_err_pid;
extern int32_t ff_err_prev;
extern double ff_Kp;
extern double ff_Ki;
extern double ff_Kd;
extern int32_t ff_err_pid_int;

extern uint32_t ff_setpoint_voltages[7];
extern float frzr_setpoint_temp[SET_POINT_COUNT];
extern float ff_setpoint_temp[SET_POINT_COUNT];
extern uint32_t frzr_setpoint_ntc[SET_POINT_COUNT];
extern float ff_setpoint_ntc[SET_POINT_COUNT];
extern uint_least8_t adc_Id_Array[4];
extern ADC_Params params;
extern ADC_Handle adc;
extern double pwm_duty;



#endif /* FRDG_GLOBAL_H_ */

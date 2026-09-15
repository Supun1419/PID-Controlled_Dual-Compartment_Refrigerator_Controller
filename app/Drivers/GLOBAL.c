#include "GLOBAL.h"


uint8_t temp_selector;
uint32_t ADC0;
uint32_t ADC1;
uint32_t ADC2;
uint32_t ADC3;
uint32_t comprsr_pwm_freq;
uint32_t comprsr_pwm_duty;
uint32_t fan_pwm_duty;
uint32_t fan_pwm_freq;
// uint8_t compressor_state;
uint8_t start_counter;
uint8_t selector;
uint32_t frzr_setpoint_voltages[7];
int32_t frzr_err;
int32_t frzr_err_sum;
uint32_t frzr_temp;
double frzr_err_pid;
int32_t frzr_err_prev;
double frzr_Kp;
double frzr_Ki;
double frzr_Kd;
int32_t frzr_err_pid_int;
int32_t temp_err_pid_int;
int32_t max_err_pid_int;
int32_t frzr_err_stp;
int32_t frzr_currnt_stp;
uint8_t init_stbl_count;
// uint8_t fan_state;
uint32_t frzr_deadband;
uint_least8_t gpio_idx;



uint8_t NV_Memory[100];
uint8_t NVM_tx_buff[100];
uint8_t NVM_rx_buff[100];
bool gpio_val;


int32_t ff_err;
uint32_t ff_temp;
int32_t ff_err_sum;
double ff_err_pid;
int32_t ff_err_prev;
double ff_Kp;
double ff_Ki;
double ff_Kd;
int32_t ff_err_pid_int;

uint32_t ff_setpoint_voltages[7];











uint8_t temp_selector;
 uint32_t ADC0;
 uint32_t ADC1;
 uint32_t ADC2;
 uint32_t ADC3;
 uint32_t comprsr_pwm_freq;
 uint32_t comprsr_pwm_duty;
 uint32_t fan_pwm_duty;
 uint32_t fan_pwm_freq;
//  uint8_t compressor_state;
 uint16_t lockout_counter;
//  uint8_t start_counter;
 uint8_t selector;
 uint32_t frzr_setpoint_voltages[7];
 int32_t frzr_err;
 int32_t frzr_err_sum;
 uint32_t frzr_temp;
 double frzr_err_pid;
 int32_t frzr_err_prev;
 double frzr_Kp;
 double frzr_Ki;
 double frzr_Kd;
 int32_t frzr_err_pid_int;
 int32_t temp_err_pid_int;
 int32_t max_err_pid_int;
 int32_t frzr_err_stp;
 int32_t frzr_currnt_stp;
 uint8_t init_stbl_count;
//  uint8_t fan_state;
 uint32_t frzr_deadband;

 PWM_Params PWMparams;
 uint_least8_t PWM_idx[PWM_NUMBER];
 PWM_Handle pwm_handl[PWM_NUMBER];

 uint8_t NV_Memory[100];
 uint8_t NVM_tx_buff[100];
 uint8_t NVM_rx_buff[100];


 int32_t ff_err;
 uint32_t ff_temp;
 int32_t ff_err_sum;
 double ff_err_pid;
 int32_t ff_err_prev;
 double ff_Kp;
 double ff_Ki;
 double ff_Kd;
 int32_t ff_err_pid_int;

 uint32_t ff_setpoint_voltages[7];
 float frzr_setpoint_temp[SET_POINT_COUNT] = {2.0f+FRZR_TEMP_OFFSET,0.0f+FRZR_TEMP_OFFSET,-2.0f+FRZR_TEMP_OFFSET,-4.0f+FRZR_TEMP_OFFSET,-8.0f+FRZR_TEMP_OFFSET,-18.0f+FRZR_TEMP_OFFSET,-20.0f+FRZR_TEMP_OFFSET};
 float ff_setpoint_temp[SET_POINT_COUNT];
uint_least8_t adc_Id_Array[4]={0};
 ADC_Params params;
 ADC_Handle adc;





































#ifndef SVC_UART_HANDLER_H_
#define SVC_UART_HANDLER_H_

#include "app/Drivers/UART.h"
#include "app/Drivers/GLOBAL.h"  // For global variables + int32 type
#include <stdint.h>

/*--------------------------------------------------------------------
 * Protocol constants
 *------------------------------------------------------------------*/
#define SOF                 0xAA
// #define EOF                 0x55

#define CMD_GET             0x01
#define CMD_SET             0x02
#define CMD_GET_RESPONSE    0x81
#define CMD_NOTIFY_DATA     0x82   /* reserved */

/*--------------------------------------------------------------------
 * Variable IDs
 *------------------------------------------------------------------*/
/* SET variables */
#define KP                                  0x01
#define KI                                  0x02
#define FRZ_TEMP_SETPOINT                   0x03
#define COMP_TEMP_SETPOINT                  0x04

/* GET variables */
#define FRZ_TEMP                            0x40
#define COMP_TEMP                           0x41

/*--------------------------------------------------------------------
 * Service API
 *------------------------------------------------------------------*/

/**
 * @brief Top-level handler, called when a full UART frame is ready
 *        in g_uart_rx_buf (including SOF/LEN/.../CRC/EOF).
 *
 * The function:
 *  - Validates SOF / EOF / LEN / CRC
 *  - Decodes cmd + payload
 *  - Calls svc_UART_get() or svc_UART_set()
 *
 * @return 0 on success, negative on error
 */
int svc_UART_handler(void);

/**
 * @brief Handle a GET command (read a variable and respond).
 *
 * @param id   variable id (FRZ_TEMP, COMP_TEMP, ...)
 * @return 0 on success, negative if unknown id
 */
int svc_UART_get(int id);

/**
 * @brief Handle a SET command (write a variable).
 *
 * @param id      variable id (KP, KI, FRZ_TEMP_SETPOINT, ...)
 * @param payload int32 value to write
 * @return 0 on success, negative if unknown id
 */
int svc_UART_set(int id, int32_t payload);

#endif /* SVC_UART_HANDLER_H_ */

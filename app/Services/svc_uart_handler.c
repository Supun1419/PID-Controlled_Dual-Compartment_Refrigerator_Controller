#include "svc_uart_handler.h"
#include <string.h>
#include <stdint.h>

/*--------------------------------------------------------------------
 * EXTERNALS FROM UART DRIVER LAYER
 *
 * These should be provided by your UART.c / parser code.
 * g_uart_rx_buf  : holds the full received frame
 * g_uart_rx_len  : number of bytes in g_uart_rx_buf
 * UART_RX_flag   : set to 1 when a full frame has been captured
 *------------------------------------------------------------------*/
extern volatile uint8_t UART_RX_flag;
extern uint8_t g_uart_rx_buf[];
extern uint8_t g_uart_rx_len;

/*--------------------------------------------------------------------
 * EXTERNAL GLOBAL VARIABLES FROM GLOBAL.h
 *
 * Replace these with the actual names/types you have in GLOBAL.h.
 *------------------------------------------------------------------*/
extern int32_t g_kp;
extern int32_t g_ki;
extern int32_t g_frz_temp_setpoint;
extern int32_t g_comp_temp_setpoint;

extern int32_t g_frz_temp;
extern int32_t g_comp_temp;

/*--------------------------------------------------------------------
 * INTERNAL HELPERS
 *------------------------------------------------------------------*/

/* Convert int32_t to big-endian byte array */
static void svc_int32_to_be(int32_t value, uint8_t out[4])
{
    uint32_t u = (uint32_t)value;
    out[0] = (uint8_t)((u >> 24) & 0xFF);
    out[1] = (uint8_t)((u >> 16) & 0xFF);
    out[2] = (uint8_t)((u >>  8) & 0xFF);
    out[3] = (uint8_t)( u        & 0xFF);
}

/* Convert big-endian byte array to int32_t */
static int32_t svc_be_to_int32(const uint8_t in[4])
{
    uint32_t u = 0;
    u |= ((uint32_t)in[0] << 24);
    u |= ((uint32_t)in[1] << 16);
    u |= ((uint32_t)in[2] <<  8);
    u |= ((uint32_t)in[3]      );
    return (int32_t)u;
}

/* XOR8 CRC over [startIdx .. endIdx] inclusive */
static uint8_t svc_crc_xor8(const uint8_t *buf, uint8_t startIdx, uint8_t endIdx)
{
    uint8_t crc = 0;
    for (uint8_t i = startIdx; i <= endIdx; i++) {
        crc ^= buf[i];
    }
    return crc;
}

/**
 * @brief Build and send a CMD_GET_RESPONSE frame:
 *
 *  SOF | LEN | CMD_GET_RESPONSE | [ID | value(4B)] | CRC | EOF
 *
 *  LEN = CMD(1) + ID(1) + value(4) = 6
 */
static void svc_send_get_response(uint8_t id, int32_t value)
{
    uint8_t frame[1 + 1 + 1 + 1 + 4 + 1 + 1]; // 10 bytes total
    uint8_t idx = 0;

    uint8_t payload[5]; // [id, value(4)]
    payload[0] = id;
    svc_int32_to_be(value, &payload[1]);

    const uint8_t lenField = 1 /* CMD */ + (uint8_t)sizeof(payload); // = 6

    frame[idx++] = SOF;
    frame[idx++] = lenField;
    frame[idx++] = CMD_GET_RESPONSE;

    // Payload
    for (uint8_t i = 0; i < sizeof(payload); i++) {
        frame[idx++] = payload[i];
    }

    // CRC over [1 .. 1+lenField] (LEN + CMD + payload)
    uint8_t crc = svc_crc_xor8(frame, 1, (uint8_t)(1 + lenField));
    frame[idx++] = crc;
    frame[idx++] = 0x55;

    // Send via your UART driver (void* buffer, uint8 size)
    Frdg_UART_Tx(frame, idx);
}

/*--------------------------------------------------------------------
 * PUBLIC API
 *------------------------------------------------------------------*/

int svc_UART_get(int id)
{
    int32_t value = 0;
    int known   = 1;

    switch (id)
    {
        case FRZ_TEMP:
            value = g_frz_temp;
            break;

        case COMP_TEMP:
            value = g_comp_temp;
            break;

        default:
            known = 0;
            break;
    }

    if (!known) {
        // Unknown GET variable ID -> ignore or add error handling
        return -1;
    }

    svc_send_get_response((uint8_t)id, value);
    return 0;
}

int svc_UART_set(int id, int32_t payload)
{
    int known = 1;

    switch (id)
    {
        case KP:
            g_kp = payload;
            break;

        case KI:
            g_ki = payload;
            break;

        case FRZ_TEMP_SETPOINT:
            g_frz_temp_setpoint = payload;
            break;

        case COMP_TEMP_SETPOINT:
            g_comp_temp_setpoint = payload;
            break;

        default:
            known = 0;
            break;
    }

    if (!known) {
        // Unknown SET variable ID
        return -1;
    }

    // Optional: send an ACK/ERROR frame here if needed
    return 0;
}

/**
 * @brief Top-level UART service handler.
 *
 * Here we use the ORIGINAL frame in g_uart_rx_buf:
 *
 *  [0] SOF (0xAA)
 *  [1] LEN (CMD + payload)
 *  [2] CMD (0x01=GET, 0x02=SET, ...)
 *  [3..] PAYLOAD
 *  [N-2] CRC
 *  [N-1] EOF (0x55)
 *
 * g_uart_rx_len is the total number of bytes in the frame.
 */
int svc_UART_handler(void)
{
    if(UART_RX_flag)
    {
        // Clear flag so we only handle once
        UART_RX_flag = 0;      
        const uint8_t *buf = g_uart_rx_buf;
        uint8_t sof = buf[0];
        if (sof != SOF) 
        {
            return -2;  // wrong SOF
        }
        uint8_t lenField = buf[1];
        // LEN = CMD + payloadLen, so total frame length:
        // total = 1(SOF) + 1(LEN) + lenField + 1(CRC) + 1(EOF)
        uint8_t expectedTotal = (uint8_t)(1 + 1 + lenField + 1 + 1);
        if (g_uart_rx_len < expectedTotal) 
        {
        // Not enough bytes yet / truncated
        return -3;
        }
        // Check EOF at end
        uint8_t eofByte = buf[expectedTotal - 1];
        if (eofByte != 0x55) 
        {
            return -4;
        }
        // CRC is just before EOF
        uint8_t crcRx = buf[expectedTotal - 2];
        uint8_t crcCalc = svc_crc_xor8(buf, 1, (uint8_t)(1 + lenField));
        if (crcRx != crcCalc) 
        {
            return -5;
        }
        // Now decode CMD + payload
        if (lenField < 1) 
        {
            // At least 1 byte for CMD
            return -6;
        }

        uint8_t cmd = buf[2];
        uint8_t payloadLen = (uint8_t)(lenField - 1);  // remove CMD byte

        const uint8_t *payload = &buf[3]; // payload starts after CMD

        switch (cmd)
        {
            case CMD_GET:
                // payload = [ID]
                if (payloadLen < 1) 
                {
                    return -7;
                }
                return svc_UART_get(payload[0]);

            case CMD_SET:
                // payload = [ID | value(4 bytes)]
                if (payloadLen < 1 + 4) 
                {
                    return -8;
                }
                {
                    uint8_t id = payload[0];
                    int32_t value = svc_be_to_int32(&payload[1]);
                    return svc_UART_set(id, value);
                }

            default:
                // Unknown command -> ignore
                return -9;
        }
    }
    else 
    {
        return -1;
    }

}

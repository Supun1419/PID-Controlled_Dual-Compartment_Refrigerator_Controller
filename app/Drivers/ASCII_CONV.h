#ifndef ASCII_CONV_H_
#define ASCII_CONV_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>

/* ======================== Includes ======================== */
void convert_from_int(int32_t num, char *arr);
void convert_from_string(const char *str, char *arr);

// --- Generic macro to select correct version ---
#define convert_to_char_array(x, arr) \
    _Generic((x), \
        int: convert_from_int, \
        const char*: convert_from_string, \
        char*: convert_from_string \
    )(x, arr)





#endif /* ASCII_CONV_H_ */

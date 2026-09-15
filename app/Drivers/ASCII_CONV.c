#include "ASCII_CONV.h"

// --- Helper 1: Integer input ---
void convert_from_int(int32_t num, char *arr) {
    sprintf(arr, "%d", num);  // convert int → string
}

// --- Helper 2: String input ---
void convert_from_string(const char *str, char *arr) {
    strcpy(arr, str);  // copy string directly
}


















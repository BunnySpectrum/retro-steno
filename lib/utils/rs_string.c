#include <stdint.h>

#include "rs_string.h"

// copy null-terminated string from src to dst
void rs_strcpy(char* dst, const char* src){
    uint8_t index = 0;
    while(src[index] != '\0'){
        dst[index] = src[index];
        index++;
    }
    dst[index] = '\0';

}
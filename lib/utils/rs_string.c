#include "rs_string.h"

// copy null-terminated string from src to dst
void rs_strcpy(char* dst, char* src){
    size_t index = 0;
    while(src[index] != '\0'){
        dst[index] = src[index];
        index++;
    }
    dst[index] = '\0';

}

size_t rs_strlen(const char* str){
    size_t count = 0;
    if(str[0] == '\0'){
        return 0;
    }

    while(str[count++] != '\0'){
        ;
    }
    return count-1;
}
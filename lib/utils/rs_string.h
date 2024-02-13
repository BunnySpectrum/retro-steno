#ifndef _RS_STRING_H_
#define _RS_STRING_H_

// #include <stdio.h>
#include "rs_stdint.h"
#include "rs_stddef.h"

void rs_strcpy(char* dst, char* src);
size_t rs_strlen(const char* str);

#endif
#ifndef _EXP_H_
#define _EXP_H_

#include "hardware/i2c.h"


void exp_search(i2c_inst_t* i2c);
uint8_t exp_check(i2c_inst_t* i2c, uint8_t addr);

#define EXP_0 0x38
#define EXP_1 0x39
#define EXP_2 0x3A
#define EXP_3 0x3B

#endif


/*
0x38
P0 - E
P1 - O
P2 - A
P3 - *

P4 - P-
P5 - #
P6 - S-
P7 - R-


*/
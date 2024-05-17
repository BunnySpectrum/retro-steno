#ifndef _EXP_H_
#define _EXP_H_

#include "hw/drv_i2c.h"


void i2c_search(void);
uint8_t exp_check(uint8_t id, uint8_t addr);

#define EXP_0 0x38
#define EXP_1 0x39
#define EXP_2 0x3A
#define EXP_3 0x3B

#endif

#define EXP_KEY_E_CHIP 0
#define EXP_KEY_E_INDEX 0

#define EXP_KEY_O_CHIP 0
#define EXP_KEY_O_INDEX 1

#define EXP_KEY_A_CHIP 0
#define EXP_KEY_A_INDEX 2

#define EXP_KEY_STAR_CHIP 0
#define EXP_KEY_STAR_INDEX 3

#define EXP_KEY_Pi_CHIP 0
#define EXP_KEY_Pi_INDEX 4

#define EXP_KEY_NUM_CHIP 0
#define EXP_KEY_NUM_INDEX 5

#define EXP_KEY_Si_CHIP 0
#define EXP_KEY_Si_INDEX 6

#define EXP_KEY_Ri_CHIP 0
#define EXP_KEY_Ri_INDEX 7
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

/*
0x39
P0 - T-
P1 - K
P2 - H
P3 - W

P4 - 
P5 - 
P6 - 
P7 - 
*/
#define EXP_KEY_Ti_CHIP 1
#define EXP_KEY_Ti_INDEX 0

#define EXP_KEY_K_CHIP 1
#define EXP_KEY_K_INDEX 1

#define EXP_KEY_H_CHIP 1
#define EXP_KEY_H_INDEX 2

#define EXP_KEY_W_CHIP 1
#define EXP_KEY_W_INDEX 3

/*
0x3A
P0 - 
P1 - -S
P2 - Z
P3 - B 

P4 - 
P5 - 
P6 - 
P7 - 
*/

#define EXP_KEY_Sf_CHIP 2
#define EXP_KEY_Sf_INDEX 1

#define EXP_KEY_Z_CHIP 2
#define EXP_KEY_Z_INDEX 2

#define EXP_KEY_B_CHIP 2
#define EXP_KEY_B_INDEX 3

/*
0x3B
P0 - -P
P1 - U
P2 - L
P3 - F

P4 - -T
P5 - -R
P6 - G
P7 - D
*/

#define EXP_KEY_Pf_CHIP 3
#define EXP_KEY_Pf_INDEX 0

#define EXP_KEY_U_CHIP 3
#define EXP_KEY_U_INDEX 1

#define EXP_KEY_L_CHIP 3
#define EXP_KEY_L_INDEX 2

#define EXP_KEY_F_CHIP 3
#define EXP_KEY_F_INDEX 3

#define EXP_KEY_Tf_CHIP 3
#define EXP_KEY_Tf_INDEX 4

#define EXP_KEY_Rf_CHIP 3
#define EXP_KEY_Rf_INDEX 5

#define EXP_KEY_G_CHIP 3
#define EXP_KEY_G_INDEX 6

#define EXP_KEY_D_CHIP 3
#define EXP_KEY_D_INDEX 7
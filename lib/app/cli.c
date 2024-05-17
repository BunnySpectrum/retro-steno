#include "cli.h"

extern void (*cmd_cb_info)(void);
extern void (*cmd_cb_stream)(void);
extern void (*cmd_cb_read)(void);
extern void (*cmd_a)(void);
extern void (*cmd_b)(void);
extern void (*cmd_c)(void);
extern void (*cmd_s)(void);

void cli_init(){
    ;
}

void cli_process(){
    int inputChar;
    
    printf("{\"msg\":");
    while(RS_CODE_ERR != rs_getchar_timeout_us(0, &inputChar)){
        // printf("%c",  inputChar);
        switch(inputChar){
            case 'r':
                cmd_cb_read();
                break;

            case 's':
                cmd_cb_stream();
                break;

            case 'i':
                cmd_cb_info();
                break;

            case 'a':
                cmd_a();
                break;
            
            case 'b':
                cmd_b();
                break;
            
            case 'c':
                cmd_c();
                break;
            
            case 'd':
                cmd_s();
                break;

        }
    }
    printf("}\n");

}


#include "log_check.h"

char printBuffer[MAX_BUF_LEN] = "";
static int bWrote;

int mock_vprintf(Logger_s logger, const char* fmt, va_list args){
    return vprintf(fmt, args);
}

int mock_vsnprintf(Logger_s logger, const char* fmt, va_list args){
    bWrote += vsnprintf(printBuffer + bWrote, MAX_BUF_LEN, fmt, args);
    return bWrote;
}

void start_log_buf(void){
    bWrote = 0;
}

void dump_buffer(void){
    printf("Logged chars: %d.\n", bWrote);
    for(int x=0; x < bWrote; x++){
        printf("%c", printBuffer[x]);
    }
    printf("\n");
}

int compare_buffer(char* buf, size_t len){
    return strncmp(printBuffer, buf, len);
}

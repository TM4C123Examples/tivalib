#include "os_serial_stdio.h"
#include "safe_stdlib.h"

void os_serial_init(void){
    safe_init();
}

void os_serial_printf(void (*p_puts)(const char *), const char * format, ...){
    char * tempBuffer;
    int bufferSize;

    va_list args;
    va_start(args, format);

    bufferSize = vsnprintf(NULL, 0,format, args);
    bufferSize++;
    tempBuffer = (char*) safe_malloc(bufferSize);
    vsnprintf(tempBuffer,bufferSize,format,args);

    va_end(args);

    p_puts(tempBuffer);
    safe_free(tempBuffer);
}

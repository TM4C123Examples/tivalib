#ifndef _OS_SERIAL_STDIO_H
#define _OS_SERIAL_STDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void os_serial_init(void);

void os_serial_printf(void (*p_puts)(const char *), const char * format, ...)
    __attribute__ ((format (printf, 2, 3)));

#endif// _OS_SERIAL_STDIO_H

#ifndef _SERIAL_STDIO_H
#define _SERIAL_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct Serial_struct{
	char (* getChar)(void);
	void (* sendChar)(char);
} Serial_t;

void serial_puts(Serial_t  serial, const char * pString);
int serial_gets(Serial_t  serial, char * pBuffer, int bufferSize);

void serial_printf(Serial_t  serial, const char * format, ...)
	__attribute__ ((format (printf, 2, 3)));

#ifdef __cplusplus
}
#endif

#endif /* _SERIAL_STDIO_H */

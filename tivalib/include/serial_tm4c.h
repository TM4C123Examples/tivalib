#ifndef _SERIAL_TM4C_H
#define _SERIAL_TM4C_H

#include "serial_stdio.h"
#include "uart_tm4c.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Serial_t serial_uart0;
		extern Serial_t serial_uart1;
		extern Serial_t serial_uart2;
    extern Serial_t serial_uart3;
		extern Serial_t serial_uart4;
		extern Serial_t serial_uart5;
		extern Serial_t serial_uart6;
		extern Serial_t serial_uart7;

#ifdef __cplusplus
}
#endif

#endif /* _SERIAL_TM4C_H */

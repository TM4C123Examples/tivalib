#include "serial_tm4c.h"

Serial_t serial_uart0 = {UART0_getChar, UART0_sendChar};
Serial_t serial_uart1 = {UART1_getChar, UART1_sendChar};
Serial_t serial_uart2 = {UART2_getChar, UART2_sendChar};
Serial_t serial_uart3 = {UART3_getChar, UART3_sendChar};
Serial_t serial_uart4 = {UART4_getChar, UART4_sendChar};
Serial_t serial_uart5 = {UART5_getChar, UART5_sendChar};
Serial_t serial_uart6 = {UART6_getChar, UART6_sendChar};
Serial_t serial_uart7 = {UART7_getChar, UART7_sendChar};

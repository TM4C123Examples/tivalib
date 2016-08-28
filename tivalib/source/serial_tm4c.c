#include "serial_tm4c.h"

Serial_t serial_uart0 = {UART0_getChar, UART0_sendChar};
Serial_t serial_uart3 = {UART3_getChar, UART3_sendChar};

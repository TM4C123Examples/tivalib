#ifndef _UART_TM4C_H
#define _UART_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif

    void UART0_init(int baudrate);
    void UART0_sendChar(char c);
    char UART0_getChar(void);

    void UART3_init(int baudrate);
    void UART3_sendChar(char c);
    char UART3_getChar(void);

#ifdef __cplusplus
}
#endif

#endif /* _UART_TM4C_H */

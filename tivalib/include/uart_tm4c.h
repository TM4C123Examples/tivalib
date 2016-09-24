#ifndef _UART_TM4C_H
#define _UART_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif

    void UART0_init(int baudrate);
    void UART0_sendChar(char c);
    char UART0_getChar(void);
		
		void UART1_init(int baudrate);
    void UART1_sendChar(char c);
    char UART1_getChar(void);
	
		void UART2_init(int baudrate);
    void UART2_sendChar(char c);
    char UART2_getChar(void);
	
    void UART3_init(int baudrate);
    void UART3_sendChar(char c);
    char UART3_getChar(void);
	
		void UART4_init(int baudrate);
		void UART4_sendChar(char c);
    char UART4_getChar(void);
		
		void UART5_init(int baudrate);
		void UART5_sendChar(char c);
    char UART5_getChar(void);
		
		void UART6_init(int baudrate);
		void UART6_sendChar(char c);
    char UART6_getChar(void);
		
		void UART7_init(int baudrate);
		void UART7_sendChar(char c);
    char UART7_getChar(void);

#ifdef __cplusplus
}
#endif

#endif /* _UART_TM4C_H */

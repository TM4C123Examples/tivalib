#include "uart_tm4c.h"
#include "TM4C123.h"

#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control

void UART0_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGC1|= SYSCTL_RCGC1_UART0;     // Encender periferico UART0
    SYSCTL->RCGC2|= SYSCTL_RCGC2_GPIOA;     // Encender periferico GPIOA
    UART0->CTL &= ~UART_CTL_UARTEN;         // Desabilitar UART0 (para configurar)
    UART0->IBRD = SystemCoreClock/(16*baudrate);                    // Divisor de frecuencia Entero
                                                                                // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART0->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
                                                                                // FBRD = round(0.12673611 * 64) = 8
    UART0->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART0->CTL|= UART_CTL_UARTEN;       // habiltar UART
    GPIOA->AFSEL |= 0x03;                       // funcion alternativa en PA[1..0]
    GPIOA->DEN |= 0x03;             // usar drivers digitales en PA[1..0]
    GPIOA->PCTL = (GPIOA->PCTL&0xFFFFFF00)+0x00000011;// configurar  PA[1..0] como pines UART
    GPIOA->AMSEL &= ~0x03;          // deshabilitar funciones analogicas en PA[1..0]
}

void UART0_sendChar(char c){
    while((UART0->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART0->DR = c;//poner dato en el buffer de transmisison
}

char UART0_getChar(void){
    while((UART0->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART0->DR)&0xFF));
}


void UART1_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGCUART|= (0x1<<1);// Encender periferico UART1
    SYSCTL->RCGCGPIO|= (0x1<<1);// Encender periferico GPIOB
    UART1->CTL &= ~UART_CTL_UARTEN;// Desabilitar UART1 (para configurar)
    UART1->IBRD = SystemCoreClock/(16*baudrate);// Divisor de frecuencia Entero
    // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART1->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
    // FBRD = round(0.12673611 * 64) = 8
    UART1->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART1->CTL|= UART_CTL_UARTEN;// habiltar UART
    GPIOB->AFSEL |= (0x1<<0)|(0x1<<1);// funcion alternativa en PB[0,1]
    GPIOB->DEN |= (0x1<<0)|(0x1<<1);// usar drivers digitales en PB[0,1]
    GPIOB->PCTL &= (uint32_t)~((0xF<<0)|((uint32_t)0xF<<4));
    GPIOB->PCTL|=((0x1<<0)|(0x1<<4));//configurar  PC[0,1] como pines UART
    GPIOB->AMSEL &=~((0x1<<0)|(0x1<<1));;          // deshabilitar funciones analogicas en PB[1..0]
}

void UART1_sendChar(char c){
    while((UART1->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART1->DR = c;//poner dato en el buffer de transmisison
}
char UART1_getChar(void){
    while((UART1->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART1->DR)&0xFF));
}

void UART2_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGCUART|= (0x1<<2);// Encender periferico UART2
    SYSCTL->RCGCGPIO|= (0x1<<3);// Encender periferico GPIOD
    UART2->CTL &= ~UART_CTL_UARTEN;// Desabilitar UART2 (para configurar)
    UART2->IBRD = SystemCoreClock/(16*baudrate);// Divisor de frecuencia Entero
    // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART2->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
    // FBRD = round(0.12673611 * 64) = 8
    UART2->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART2->CTL|= UART_CTL_UARTEN;// habiltar UART

		GPIOD->LOCK=(0x4C4F434B); //desbloqueo del peroferico D
    GPIOD->CR=(0x1<<7);	//para uso del Pin 7

    GPIOD->AFSEL |= (0x1<<6)|(0x1<<7);// funcion alternativa en PD[6,7]
    GPIOD->DEN |= (0x1<<6)|(0x1<<7);// usar drivers digitales en PD[6,7]
    GPIOD->PCTL &= (uint32_t)~((0xF<<24)|((uint32_t)0xF<<28));
    GPIOD->PCTL|=((0x1<<24)|(0x1<<28));//configurar  PD[6,7] como pines UART
    GPIOD->AMSEL &=~((0x1<<6)|(0x1<<7));;          // deshabilitar funciones analogicas en PD[1..0]
}

void UART2_sendChar(char c){
    while((UART2->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART2->DR = c;//poner dato en el buffer de transmisison
}
char UART2_getChar(void){
    while((UART2->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART2->DR)&0xFF));
}

void UART3_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGCUART|= (0x1<<3);// Encender periferico UART3
    SYSCTL->RCGCGPIO|= (0x1<<2);// Encender periferico GPIOC
    UART3->CTL &= ~UART_CTL_UARTEN;// Desabilitar UART3 (para configurar)
    UART3->IBRD = SystemCoreClock/(16*baudrate);// Divisor de frecuencia Entero
    // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART3->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
    // FBRD = round(0.12673611 * 64) = 8
    UART3->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART3->CTL|= UART_CTL_UARTEN;// habiltar UART
    GPIOC->AFSEL |= (0x1<<6)|(0x1<<7);// funcion alternativa en PC[6,7]
    GPIOC->DEN |= (0x1<<6)|(0x1<<7);// usar drivers digitales en PC[6,7]
    GPIOC->PCTL &= (uint32_t)~((0xF<<24)|((uint32_t)0xF<<28));
    GPIOC->PCTL|=((0x1<<24)|(0x1<<28));//configurar  PC[6,7] como pines UART
    GPIOC->AMSEL &=~((0x1<<6)|(0x1<<7));;          // deshabilitar funciones analogicas en PC[1..0]
}

void UART3_sendChar(char c){
    while((UART3->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART3->DR = c;//poner dato en el buffer de transmisison
}
char UART3_getChar(void){
    while((UART3->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART3->DR)&0xFF));
}

void UART4_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGCUART|= (0x1<<4);// Encender periferico UART4
    SYSCTL->RCGCGPIO|= (0x1<<2);// Encender periferico GPIOC
    UART4->CTL &= ~UART_CTL_UARTEN;// Desabilitar UART4 (para configurar)
    UART4->IBRD = SystemCoreClock/(16*baudrate);// Divisor de frecuencia Entero
    // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART4->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
    // FBRD = round(0.12673611 * 64) = 8
    UART4->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART4->CTL|= UART_CTL_UARTEN;// habiltar UART
    GPIOC->AFSEL |= (0x1<<4)|(0x1<<5);// funcion alternativa en PC[6,7]
    GPIOC->DEN |= (0x1<<4)|(0x1<<5);// usar drivers digitales en PC[6,7]
    GPIOC->PCTL &= (uint32_t)~((0xF<<16)|((uint32_t)0xF<<20));
    GPIOC->PCTL|=((0x1<<16)|(0x1<<20));//configurar  PC[6,7] como pines UART
    GPIOC->AMSEL &=~((0x1<<4)|(0x1<<5));;          // deshabilitar funciones analogicas en PC[1..0]
}

void UART4_sendChar(char c){
    while((UART4->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART4->DR = c;//poner dato en el buffer de transmisison
}
char UART4_getChar(void){
    while((UART4->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART4->DR)&0xFF));
}

void UART5_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGCUART|= (0x1<<5);// Encender periferico UART5
    SYSCTL->RCGCGPIO|= (0x1<<4);// Encender periferico GPIOE
    UART5->CTL &= ~UART_CTL_UARTEN;// Desabilitar UART5 (para configurar)
    UART5->IBRD = SystemCoreClock/(16*baudrate);// Divisor de frecuencia Entero
    // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART5->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
    // FBRD = round(0.12673611 * 64) = 8
    UART5->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART5->CTL|= UART_CTL_UARTEN;// habiltar UART
    GPIOE->AFSEL |= (0x1<<4)|(0x1<<5);// funcion alternativa en PE[4,5]
    GPIOE->DEN |= (0x1<<4)|(0x1<<5);// usar drivers digitales en PE[4,5]
    GPIOE->PCTL &= (uint32_t)~((0xF<<16)|((uint32_t)0xF<<20));
    GPIOE->PCTL|=((0x1<<16)|(0x1<<20));//configurar  PE[4,5] como pines UART
    GPIOE->AMSEL &=~((0x1<<4)|(0x1<<5));          // deshabilitar funciones analogicas en PE[1..0]
}

void UART5_sendChar(char c){
    while((UART5->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART5->DR = c;//poner dato en el buffer de transmisison
}
char UART5_getChar(void){
    while((UART5->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART5->DR)&0xFF));
}

void UART6_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGCUART|= (0x1<<6);// Encender periferico UART6
    SYSCTL->RCGCGPIO|= (0x1<<3);// Encender periferico GPIOD
    UART6->CTL &= ~UART_CTL_UARTEN;// Desabilitar UART4 (para configurar)
    UART6->IBRD = SystemCoreClock/(16*baudrate);// Divisor de frecuencia Entero
    // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART6->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
    // FBRD = round(0.12673611 * 64) = 8
    UART6->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART6->CTL|= UART_CTL_UARTEN;// habiltar UART
    GPIOD->AFSEL |= (0x1<<4)|(0x1<<5);// funcion alternativa en PD[4,5]
    GPIOD->DEN |= (0x1<<4)|(0x1<<5);// usar drivers digitales en PD[4,5]
    GPIOD->PCTL &= (uint32_t)~((0xF<<16)|((uint32_t)0xF<<20));
    GPIOD->PCTL|=((0x1<<16)|(0x1<<20));//configurar  PD[4,5] como pines UART
    GPIOD->AMSEL &=~((0x1<<4)|(0x1<<5));;          // deshabilitar funciones analogicas en PD[1..0]
}

void UART6_sendChar(char c){
    while((UART6->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART6->DR = c;//poner dato en el buffer de transmisison
}
char UART6_getChar(void){
    while((UART6->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART6->DR)&0xFF));
}

void UART7_init(int baudrate){
    SystemCoreClockUpdate();
    SYSCTL->RCGCUART|= (0x1<<7);// Encender periferico UART7
    SYSCTL->RCGCGPIO|= (0x1<<4);// Encender periferico GPIOE
    UART7->CTL &= ~UART_CTL_UARTEN;// Desabilitar UART4 (para configurar)
    UART7->IBRD = SystemCoreClock/(16*baudrate);// Divisor de frecuencia Entero
    // IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
    UART7->FBRD=(int)(((SystemCoreClock/(16*baudrate))-(SystemCoreClock/(16.0*baudrate)))*16);// Divisor de frecuencia faccional
    // FBRD = round(0.12673611 * 64) = 8
    UART7->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
    UART7->CTL|= UART_CTL_UARTEN;// habiltar UART
    GPIOE->AFSEL |= (0x1<<0)|(0x1<<1);// funcion alternativa en PE[0,1]
    GPIOE->DEN |= (0x1<<0)|(0x1<<1);// usar drivers digitales en PE[0,1]
    GPIOE->PCTL &= (uint32_t)~((0xF<<0)|((uint32_t)0xF<<4));
    GPIOE->PCTL|=((0x1<<0)|(0x1<<4));//configurar  PC[0,1] como pines UART
    GPIOE->AMSEL &=~((0x1<<0)|(0x1<<1));;          // deshabilitar funciones analogicas en PE[1..0]
}

void UART7_sendChar(char c){
    while((UART7->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
    UART7->DR = c;//poner dato en el buffer de transmisison
}
char UART7_getChar(void){
    while((UART7->FR&UART_FR_RXFE) != 0);
    return ((unsigned char)((UART7->DR)&0xFF));
}

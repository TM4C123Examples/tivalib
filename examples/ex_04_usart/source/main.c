#include "uart_tm4c.h"
#include "delay.h"

int main(){
    UART0_init(9600);
    while(1){
        UART0_sendChar('g');
        UART0_sendChar('\n');
        delay_ms(1000);
    }
}

#include "serial_tm4c.h"
#include "delay.h"

int main(){
    UART0_init(9600);
    while(1){
        serial_printf(serial_uart0,"Hello, World!\n");
        delay_ms(1000);
    }
}

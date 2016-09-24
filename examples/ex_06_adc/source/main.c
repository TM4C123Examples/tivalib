#include "serial_tm4c.h"
#include "delay.h"
#include "adc_tm4c.h"

int main(){
    int adc_data=0;
    UART0_init(9600);
    adc_init();
    serial_printf(serial_uart0,"\nSystem ready!\n");
    while(1){
        adc_data=adc_read(0);
        serial_printf(serial_uart0,"adc = %d\n", adc_data);
        delay_ms(1000);
    }
}


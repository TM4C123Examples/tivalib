#include "serial_tm4c.h"

#define BUFFER_SIZE 80

char myBuffer[BUFFER_SIZE];

int main(){
    UART2_init(9600);
    serial_printf(serial_uart2,"\nEcho example\n");
    while(1){
        serial_printf(serial_uart2,"Enter string to echo: \n");
        serial_gets(serial_uart2,myBuffer,BUFFER_SIZE);
        serial_printf(serial_uart2,">>%s\n",myBuffer);
    }
}

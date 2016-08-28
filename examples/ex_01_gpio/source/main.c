#include "board_tm4c123gxl.h"
#include "delay.h"

int main(){
    led_init();
    while(1){
        led_set_color(0xF);
        delay_ms(500);
        led_set_color(0x0);
        delay_ms(500);
    }
}


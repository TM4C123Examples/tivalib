#include "board_tm4c123gxl.h"
#include "delay.h"

int main(){
    led_init();
    while(1){
        led_set_color(LED_BLACK);
        delay_ms(500);
        led_set_color(LED_WHITE);
        delay_ms(500);
    }
}


#include "board_tm4c123gxl.h"
#include "timer_tm4c.h"

void timer0_callback(void);

int main(){
    led_init();
    timer0_init(500,TIMER_BASETIME_MS,timer0_callback);
    timer0_start();
    while(1){
    }
}

int last_state = 0;
void timer0_callback(void){
    if(last_state){
        led_set_color(LED_WHITE);
    }else{
        led_set_color(LED_BLACK);
    }
    last_state = !last_state;
}

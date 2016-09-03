#include "board_tm4c123gxl.h"
#include "delay.h"

void buttons_callback(int sw1_state,int sw2_state);

int main(){
    buttons_interupt_init(buttons_callback);
    led_init();
    while(1){
    }
}

void buttons_callback(int sw1_state,int sw2_state){
    if(sw1_state){
        led_set_color(LED_GREEN);
    }
    else{
        led_set_color(LED_BLACK);
    }
    if(sw2_state){
        led_set_color(LED_BLUE);
    }
    else{
      led_set_color(LED_BLACK);
    }
}

#include "board_tm4c123gxl.h"
#include "delay.h"
int main(){
	led_init();
    buttons_init();
	while(1){
    if (get_button_sw1(0))
        led_set_color(LED_GREEN);
    else
        led_set_color(LED_BLACK);
    
    if (get_button_sw2(0))
        led_set_color(LED_BLUE);
    else
        led_set_color(LED_BLACK);
    }
}

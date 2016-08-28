#include "board_tm4c123gxl.h"
#include "delay.h"
int main(){
	led_init();
    button_init();
	while(1){
    if (get_button_sw1(1))
        led_set_color(LED_GREEN);
    else
        led_set_color(LED_BLACK);
    }
}

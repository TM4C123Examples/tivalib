#include "board_tm4c123gxl.h"
#include "delay.h"
int main(){
    led_init();
    buttons_init();
    while(1){
    if (button_get_sw1())
        led_set_color(LED_GREEN);
    else
        led_set_color(LED_BLACK);

    if (button_get_sw2())
        led_set_color(LED_BLUE);
    else
        led_set_color(LED_BLACK);
    }
}

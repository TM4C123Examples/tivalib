#include "board_tm4c123gxl.h"

void delay_ms(void);

int main(){
    led_init();
    while(1){
          led_set_color(0xF);
          delay_ms();
          led_set_color(0xF);
          delay_ms();
    }
}

void delay_ms(void){
    int a=0;
    for(int i=0; i<500000; i++){
         a++;
    }
}

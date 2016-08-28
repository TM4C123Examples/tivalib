#include "TM4C123.h" // Device header
#include "board_tm4c123gxl.h"

void led_init(void){
    SYSCTL->RCGCGPIO|=(0x01)<<5;  //0x01
    GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
    GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
}

void led_set_color(int color){
    GPIOF->DATA=color;
}

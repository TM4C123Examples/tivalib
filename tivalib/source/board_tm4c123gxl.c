#include "TM4C123.h" // Device header
#include "board_tm4c123gxl.h"

static void (*_buttons_callback)(int,int);

void led_init(void){
    SYSCTL->RCGCGPIO|=(0x01)<<5;  //0x01
    GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
    GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
}

void buttons_init(void){
    SYSCTL->RCGCGPIO|=(0x1<<5);//Activamos Periferico GPIOF
    GPIOF->LOCK=(0x4C4F434B);
    GPIOF->CR=(0x1<<0);

    GPIOF->DEN|=(0x1<<0)|(0x1<<4);
    GPIOF->PUR|=(0x1<<0)|(0x1<<4);
}

//input is SW1==PF4 SW"== PF0 use pull ups
void buttons_interupt_init(void (*callback_p)(int,int)){
    _buttons_callback = callback_p;
    buttons_init();
    GPIOF->IBE|=(0x1<<4)|(0x1<<0);//both edeges interrupt sensing
    GPIOF->IM=(0x1<<4)|(0x1<<0);//Disable the interrupt mask for GPIOF[4]
    GPIOF->ICR=(0x1<<4)|(0x1<<0);//clear previous interrupts events for GPIOF[4]
    NVIC_EnableIRQ(GPIOF_IRQn);
}

void led_set_color(int color){
    ((uint32_t*)GPIOF)[LED_WHITE]=color;
}

int  button_get_sw1(void){
    if (((GPIOF->DATA&(0x1<<4))))
        return 0;
    else
        return 1;
}

int  button_get_sw2(void){
    if (((GPIOF->DATA&(0x1<<0))))
        return 0;
    else
        return 1;
}

void GPIOF_Handler(void){
    GPIOF->ICR=(0x1<<4)||(0x1<<0);//clear previous interrupts events for GPIOF[4&0]
    //User code
    _buttons_callback((((GPIOF->DATA>>4)&0x1)==0),(((GPIOF->DATA>>0)&0x1)==0));
}

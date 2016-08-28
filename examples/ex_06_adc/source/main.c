#include "board_tm4c123gxl.h"
#include "delay.h"
#include "TM4C123.h"                    // Device header
void buttons_interupt_init(void);

int main(){
    buttons_interupt_init();
    led_init();
    NVIC_EnableIRQ(GPIOF_IRQn);
	while(1) ;

}


//input is SW1==PF4 SW"== PF0 use pull ups
void buttons_interupt_init(void){
	SYSCTL->RCGCGPIO|=((0x1)<<5);//enable GPIOF peripherial
    GPIOF->LOCK=(0x4C4F434B); // eneble sw2
    GPIOF->CR=(0x1<<0);// sure eneble sw2
	GPIOF->DEN|=(0x1<<4)|(0x1<<0);//enable GPIOF[4&0] as digital IO
	GPIOF->PUR=(0x1<<4)|(0x1<<0);//GPIOF[4] and GPIOF[0]is using PullUp resitors
	GPIOF->IBE|=(0x1<<4)|(0x1<<0);//both edeges interrupt sensing
	GPIOF->IM=(0x1<<4)|(0x1<<0);//Disable the interrupt mask for GPIOF[4]
	GPIOF->ICR=(0x1<<4)|(0x1<<0);//clear previous interrupts events for GPIOF[4]
}

void GPIOF_Handler(void){
	GPIOF->ICR=(0x1<<4)||(0x1<<0);//clear previous interrupts events for GPIOF[4&0]
	//User code
	if(((GPIOF->DATA>>4)&0x1)==0){
		led_set_color(LED_GREEN);
	}
    else{
        led_set_color(LED_BLACK);
	}
    if(((GPIOF->DATA>>0)&0x1)==0){
		led_set_color(LED_BLUE);
	}
    else{
      led_set_color(LED_BLACK);
	}
}

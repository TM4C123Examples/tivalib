#include "TM4C123.h"                    // Device header
#include "pwm_tm4c.h"

void pwm0_0_init(void){
    //Configure PB6 as alternate function for M0PWM0
    SYSCTL->RCGCGPIO |= (0x1<<1);//Turn on GPIOB
    while(!(SYSCTL->PRGPIO & (0x1<<1)));
    
    GPIOB->DEN |= (0x1<<6);//digital functions
    GPIOB->AFSEL |= (0x1<<6);//alternate functions
    
    GPIOB->PCTL &= ~(0xF<<24);//Connect Pin6 to alternate function 4 (m0pwm0)
    GPIOB->PCTL |= (0x4<<24);//Connect Pin6 to alternate function 4 (m0pwm0)

    
    //SYSCTL->RCC |= (0x1<<20);// Use pwm div
    //SYSCTL->RCC |= (0x7<<17);// divide system clock by 64
    
    SYSCTL->RCGCPWM |= (0x1<<0);//Turn on PWM0
    while(!(SYSCTL->PRPWM & (0x1<<0)));
    
    PWM0->_0_CTL = 0;
    PWM0->_0_GENA = 0x8C;
    PWM0->_0_GENB = 0x8C;
    PWM0->_0_LOAD = 10000;
    PWM0->_0_CMPA = 5000;
    PWM0->_0_CMPB = 4000;
    PWM0->_0_CTL = (0x1<<2)|0x1<<0;    
    PWM0->ENABLE = 1;  
}

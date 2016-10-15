#include "TM4C123.h"                    // Device header
#include "pwm_tm4c.h"

void pwm0_AB_init(float frequency,int mode,float pwm_a_initial_dc,float pwm_b_initial_dc){
    //Configure PB6 as alternate function for M0PWM0
    if((mode == PWM_A_ONLY)||(mode == PWM_A_AND_B)){
        SYSCTL->RCGCGPIO |= (0x1<<1);//Turn on GPIOB
        while(!(SYSCTL->PRGPIO & (0x1<<1)));

        GPIOB->DEN |= (0x1<<6);//digital functions
        GPIOB->AFSEL |= (0x1<<6);//alternate functions

        GPIOB->PCTL &= ~(((uint32_t)0xF)<<(24));
        GPIOB->PCTL |= (((uint32_t)0x4)<<(24));//Connect Pin6 to alternate function 4 (m0pwm0)
    }
    //Configure PB7 as alternate function for M0PWM1
    if((mode == PWM_B_ONLY)||(mode == PWM_A_AND_B)){
        SYSCTL->RCGCGPIO |= (0x1<<1);//Turn on GPIOB
        while(!(SYSCTL->PRGPIO & (0x1<<1)));

        GPIOB->DEN |= (0x1<<7);//digital functions
        GPIOB->AFSEL |= (0x1<<7);//alternate functions

        GPIOB->PCTL &= ~(((uint32_t)0xF)<<(28));
        GPIOB->PCTL |= (((uint32_t)0x4)<<(28));//Connect Pin7 to alternate function 4 (m0pwm1)
    }

    SYSCTL->RCC |= (0x1<<20);// Use pwm div
    SYSCTL->RCC |= (0x7<<17);// divide system clock by 64

    SYSCTL->RCGCPWM |= (0x1<<0);//Turn on PWM0
    while(!(SYSCTL->PRPWM & (0x1<<0)));

    SystemCoreClockUpdate();
    int load_value = (int)((SystemCoreClock/(64.0f*frequency)))-1;

    PWM0->_0_CTL = 0;
    PWM0->_0_GENA = (0x3<<6)|(0x2<<0);
    PWM0->_0_GENB = (0x3<<10)|(0x2<<0);
    PWM0->_0_LOAD = load_value;
    PWM0->_0_CMPA = (int)((load_value+1) * pwm_a_initial_dc/100);
    PWM0->_0_CMPB = (int)((load_value+1) * pwm_b_initial_dc/100);
    PWM0->_0_CTL = (0x1<<2)|0x1<<0;

    if(mode == PWM_A_ONLY){
        PWM0->ENABLE |= 0x1<<0;
    }else if(mode == PWM_B_ONLY){
        PWM0->ENABLE |= 0x1<<1;
    }else{
        PWM0->ENABLE |= (0x1<<0)|(0x1<<1);
    }
}

void pwm0_A_set_dc(float pwm_dc){
    PWM0->_0_CMPA = (int)((PWM0->_0_LOAD+1)* pwm_dc/100);
}

void pwm0_B_set_dc(float pwm_dc){
    PWM0->_0_CMPB = (int)((PWM0->_0_LOAD+1)* pwm_dc/100);
}

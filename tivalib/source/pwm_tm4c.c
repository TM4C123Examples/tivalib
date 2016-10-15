#include "TM4C123.h"                    // Device header
#include "pwm_tm4c.h"

void gpio_set_af(GPIOA_Type *gpio,uint32_t pin,uint32_t af_select);
void gpio_peripheral_enable(GPIOA_Type *gpio);
int gpio_get_peripheral_index(GPIOA_Type *gpio);

void gpio_set_af(GPIOA_Type *gpio,uint32_t pin,uint32_t af_select){
        gpio->DEN |= (0x1<<pin);//digital functions
        gpio->AFSEL |= (0x1<<pin);//alternate functions
        gpio->PCTL &= ~(((uint32_t)0xF)<<(pin*4));
        gpio->PCTL |= (((uint32_t)af_select)<<(pin*4));//Connect Pin6 to alternate function 4 (m0pwm0)
}

void gpio_peripheral_enable(GPIOA_Type *gpio){
    int p_index = gpio_get_peripheral_index(gpio);
    SYSCTL->RCGCGPIO |= (0x1<<p_index);
    while(!(SYSCTL->PRGPIO & (0x1<<p_index)));
}

int gpio_get_peripheral_index(GPIOA_Type *gpio){
    uint32_t address = (uint32_t) gpio;
    return (address-GPIOA_BASE)/(GPIOB_BASE-GPIOA_BASE);
}

void pwm0_AB_init(float frequency,int mode,float pwm_a_initial_dc,float pwm_b_initial_dc){
    //Configure PB6 as alternate function for M0PWM0
    if((mode == PWM_A_ONLY)||(mode == PWM_A_AND_B)){
        gpio_peripheral_enable(GPIOB);
        gpio_set_af(GPIOB,6,4);//Connect Pin6 to alternate function 4 (m0pwm0)
    }
    //Configure PB7 as alternate function for M0PWM1
    if((mode == PWM_B_ONLY)||(mode == PWM_A_AND_B)){
        gpio_peripheral_enable(GPIOB);
        gpio_set_af(GPIOB,7,4);//Connect Pin7 to alternate function 4 (m0pwm1)
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

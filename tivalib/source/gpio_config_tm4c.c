#include "gpio_config_tm4c.h"

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


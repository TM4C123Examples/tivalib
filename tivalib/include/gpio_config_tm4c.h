#ifndef _GPIO_CONFIG_TM4C_H
#define _GPIO_CONFIG_TM4C_H

#include "TM4C123.h"                    // Device header

#ifdef __cplusplus
extern "C" {
#endif

void gpio_set_af(GPIOA_Type *gpio,uint32_t pin,uint32_t af_select);
void gpio_peripheral_enable(GPIOA_Type *gpio);
int gpio_get_peripheral_index(GPIOA_Type *gpio);

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_CONFIG_TM4C_H */

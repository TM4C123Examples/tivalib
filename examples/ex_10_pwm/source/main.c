#include "pwm_tm4c.h"
#include "delay.h"

int main(){
    pwm_init(PWMCHANNEL_P0PWM0,500,50);
    pwm_init(PWMCHANNEL_P0PWM1,500,30);
    while(1){
        delay_ms(1000);
        pwm_set_dc(PWMCHANNEL_P0PWM0,10);
        pwm_set_dc(PWMCHANNEL_P0PWM1,40);
        delay_ms(1000);
        pwm_set_dc(PWMCHANNEL_P0PWM0,50);
        pwm_set_dc(PWMCHANNEL_P0PWM1,30);
    }
}

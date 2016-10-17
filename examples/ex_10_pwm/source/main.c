#include "pwm_tm4c.h"
#include "delay.h"

int main(){
    pwm0_AB_init(500,PWM_A_AND_B,50,30);
    while(1){
        delay_ms(2000);
        pwm0_A_set_dc(80);
        pwm0_B_set_dc(15);
        delay_ms(2000);
        pwm0_A_set_dc(50);
        pwm0_B_set_dc(60);
    }
}

#include "board_tm4c123gxl.h"
#include "delay.h"
int sample=0;
int main(){
    adc_init();
    while(1){
        sample=adc_read();
        delay_ms(500);
        
    }
}

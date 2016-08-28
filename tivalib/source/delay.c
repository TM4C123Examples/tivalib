#include "delay.h"
#include <stdint.h>

void SystemCoreClockUpdate(void);
extern uint32_t SystemCoreClock;

void delay_ms(int delay_time){
    SystemCoreClockUpdate();
    uint32_t ms_count = (SystemCoreClock/(1000*6));
    for(int i=0; i<delay_time*ms_count; i++){
    }
}

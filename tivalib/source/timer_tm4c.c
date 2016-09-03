#include "timer_tm4c.h"
#include "TM4C123.h"

static void (*_timer0_callback)(void);

/**
 * @brief init timer as 32 timer
 **/
void timer0_init(int period,int base,void(*p_callback)(void)){
    _timer0_callback = p_callback;
    SystemCoreClockUpdate();

    SYSCTL->RCGCTIMER|=0x1;//Enable peripherial timer0
    TIMER0->CTL=0x00;//Disable timer during configuration
    TIMER0->CFG=0x00;// a/b chained as 32 bit
    TIMER0->TAMR=(0x0<<4)|(0x02);//TAM as periodic timer/ down timer
    TIMER0->TAILR=((period)*(SystemCoreClock/((base==TIMER_BASETIME_MS)?1000:1000000)))-1;//set top value
    TIMER0->CTL=(0x1<<1)|(0x1<<5);//Enable debug stall and ADC triggering

    NVIC_EnableIRQ(TIMER0A_IRQn);
    TIMER0->IMR=0x01;
}


void timer0_start(void){
    TIMER0->CTL|=(0x1<<0);//Start Timer
}

void timer0_stop(void){
    TIMER0->CTL&=~((unsigned int) 0x01);//Stop Timer
}

void TIMER0A_Handler(){
    TIMER0->ICR = (0x01<<0);//clear interrupt flag
    _timer0_callback();
}

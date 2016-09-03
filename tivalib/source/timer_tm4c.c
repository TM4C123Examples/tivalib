#include "timer_tm4c.h"
#include "TM4C123.h"

static void (*_timer0_callback)(void);

void timer0_init(int period,int base,void(*p_callback)(void)){
    _timer0_callback = p_callback;
    SystemCoreClockUpdate();
    
    SYSCTL->RCGCTIMER|=0x1;//Enable peripherial timer0
    TIMER0->CTL=0x00;//Disable timer during configuration
    TIMER0->CFG=0x4;// a/b 16 bit mode
    TIMER0->TAMR=(0x0<<4)|(0x02);//TAM as periodic timer/ down timer
    TIMER0->TAILR=0x01;//set top value as 0x01
    TIMER0->TAPR=0x0;//set prescaler to 0x00
    TIMER0->CTL=(0x1<<1)|(0x1<<5);//Enable debug stall and ADC triggering
}

void timerSet(unsigned int count, unsigned char prescale){
    timer0_stop();
    TIMER0->TAILR=count;
    TIMER0->TAPR=prescale;
}

void timer0_start(void){
    TIMER0->CTL|=0x01;//Start Timer
}

void timer0_stop(void){
    TIMER0->CTL&=~((unsigned int) 0x01);//Stop Timer
}

void timerIRQConfig(unsigned int enable){
    if(enable){
        NVIC_EnableIRQ(TIMER0A_IRQn);
        TIMER0->IMR=0x01;
    }else{
        NVIC_DisableIRQ(TIMER0A_IRQn);
        TIMER0->IMR=0x00;
    }
}

void TIMER0A_Handler(){
    TIMER0->ICR=0x01;//clear interrupt flag
    _timer0_callback();
}

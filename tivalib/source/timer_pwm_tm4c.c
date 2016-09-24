#include "TM4C123.h" // Device header
#include "timer_pwm_tm4c.h"
int frequence = 0;
 

void timer0_pwm_set(float duty_cycle){
	if(duty_cycle<=0){
		TIMER0->TAMATCHR=(frequence); //ciclo de trabajo 0
	}else if(duty_cycle>=100){
		TIMER0->TAMATCHR=0xFFFF; //ciclo de trabajo 100
	}else if(duty_cycle>0&&duty_cycle<100){
		TIMER0->TAMATCHR=(frequence)-((int)((duty_cycle/100)*(frequence)));
	}
}

int timer0_pwm_init(int frequency_timer){
    SystemCoreClockUpdate();
	SYSCTL->RCGCGPIO|=0x3F;//Habilitamos todos los GPIO
	GPIOF->DEN|=0x1<<1;
	GPIOF->DIR|=0x1<<1;
	GPIOF->DATA&=~(0x1<<1);
	SYSCTL->RCGCTIMER|=(0x1<<0);//Habilitamos Timer0;
	//configuramos pin B6 como T0CCP0 para alimentar el counter 0;
	GPIOB->DEN|=(0x1<<6);//funcines digitales
	GPIOB->DIR|=(0x1<<6);//salida
	GPIOB->AFSEL|=(0x1<<6);//modo alternativo
	GPIOB->PCTL&=~(0xF<<24);
	GPIOB->PCTL|=(0x7<<24);//pin es T0CCP0


	TIMER0->CTL&=~((0x1<<0)|(0x1<<8));//Limpia los bits TbEN TaEN para desabilitar el timer a,b
																		//durante la configuracion

	TIMER0->CFG|=0x4;//TimerA y timerB en modo separado de 16Bits

	//configura timer como PWM
	TIMER0->TAMR|=(0x2<<0);// Timer a en modo timer periodico
	TIMER0->TAMR&=~(0x1<<2);//modo contador de flancos (nesesario para PWM)
	TIMER0->TAMR|=(0x1<<3);//modo alternativo de timer: PWM
	TIMER0->TAMR&=~(0x1<<4);//counter down(Necesario para PWM)

	//Valores de control de periodo de timer  periodo en ciclos =(TAPR<<16)|TAILR
    frequence =(SystemCoreClock/frequency_timer);
	TIMER0->TAILR=frequence - 1; //FREQ= (sysClockFreq/pwmFreq)-1
	TIMER0->TAPR=0x00;
 
	//Valores de control de ciclo de trabajo
	TIMER0->TAMATCHR=frequence - 1; //ciclo de trabajo 0, 
	TIMER0->TAPMR=0x00;
	TIMER0->CTL|=0x1<<0;//inicia PWM
}

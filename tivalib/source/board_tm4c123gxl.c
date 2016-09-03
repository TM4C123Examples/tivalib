#include "TM4C123.h" // Device header
#include "board_tm4c123gxl.h"

void led_init(void){
    SYSCTL->RCGCGPIO|=(0x01)<<5;  //0x01
    GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
    GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
}

void buttons_init(void){
    SYSCTL->RCGCGPIO|=(0x1<<5);//Activamos Periferico GPIOF
    GPIOF->LOCK=(0x4C4F434B);//desbloqueo del  buton 2
    GPIOF->CR=(0x1<<0);

    GPIOF->DEN|=(0x1<<0)|(0x1<<4);
    GPIOF->PUR|=(0x1<<0)|(0x1<<4);
}

void led_set_color(int color){
    ((uint32_t*)GPIOF)[LED_WHITE]=color;
}

int  button_get_sw1(void){
    if (((GPIOF->DATA&(0x1<<4))))
        return 0;
    else
        return 1;
}

int  button_get_sw2(void){
    if (((GPIOF->DATA&(0x1<<0))))
        return 0;
    else
        return 1;
}

void adc_init(){
	/*Configuracion de Pines*/
	SYSCTL->RCGCGPIO=(0x1<<1)|(0x1<<3)|(0x1<<4); //configuramos puertos B D E
	SYSCTL->RCGCADC|=0x01;//habilitamos ADC0
	
	GPIOE->DEN&=~((0x1<<4)|(0x1<<5));// habilitamos los pines  PE4 y PE5
	GPIOB->DEN&=~((0x1<<4)|(0x1<<5));// Habilitamos los pines PB4 y PB5
	GPIOE->AMSEL|=(0x1<<4)|(0x1<<5);// utilizamos funcion alternativa AIN8 AIN9
	GPIOB->AMSEL|=(0x1<<4)|(0x1<<5);//  utilizamos funcion alternativa AIN10 AIN11
	
	//Configuracion ADC principal pagina 818
	
	ADC0->ACTSS&=~(0xF);//desactivamos secuenciadores durantes la configuracion
	ADC0->EMUX=0; //para trigger por sofware (default)
	
	//Configuracion del sequenciador
	ADC0->SSMUX0=(0x8)|(0x9<<4)|(0xA<<8)|(0xB<<12);
	ADC0->SSCTL0=(0x1<<14)|(0x1<<13);//Final de secuencia en muestra 3, y genera interrupcion
	//Desenmacaramos interrupcion por secuenciador 0
	ADC0->IM&=~(0x0<<0); //  desactivamos las interrupciones         
	ADC0->ACTSS|=(0x1<<0);//activamos secuenciador 0
}

int adc_read(void){
	ADC0->PSSI=(0x1<<0);//inicia secuendiador 0
    if(ADC0->SSFSTAT0&(0x1<<8)){ //inicio de lectura
        return ADC0->SSFIFO0;
         }
         
}

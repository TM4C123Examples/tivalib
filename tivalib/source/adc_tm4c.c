#include "TM4C123.h" // Device header
#include "adc_tm4c.h"



void adc_init(){
    /*Configuracion de Pines*/
    SYSCTL->RCGCGPIO=(0x1<<1)|(0x1<<4); //configuramos puertos B E
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

int adc_read(int select_channel){
    int adc_data;
    int adc_result = 0;
    ADC0->PSSI=(0x1<<0);//trigger sequence
    for(int i = 0; i < 4; i++){
        while((ADC0->SSFSTAT0&(0x1<<8))); //while empty
        adc_data = ADC0->SSFIFO0;
        if(select_channel == i){
            adc_result = adc_data;
        }
    }
    return adc_result;
}

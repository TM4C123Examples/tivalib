#include "board_tm4c123gxl.h"
#include "delay.h"
#include "TM4C123.h"                    // Device header


void ADC_init(void);
void start_ADC(void);

int ADC_samples[4];
int ADC_sampleOk=0;
int ADC_sampleEnd=1;
int a=0;


int main(){
	ADC_samples[0]=0;
	ADC_samples[1]=0;
	ADC_samples[2]=0;
	ADC_samples[3]=0;
	
	ADC_init();
	NVIC_EnableIRQ(ADC0SS0_IRQn); 
	while(1){
		if(ADC_sampleEnd){
			start_ADC();
	}
		a++;
	}
}

void start_ADC(){
	ADC0->PSSI=(0x1<<0);//inicia secuendiador 0
	ADC_sampleEnd=0;
}

void ADC_init(){
	/*Configuracion de Pines*/
	SYSCTL->RCGCGPIO=(0x1<<1)|(0x1<<3)|(0x1<<4); //configuramos puertos B D E
	SYSCTL->RCGCADC|=0x01;//habilitamos ADC0
	
	GPIOE->DEN&=~((0x1<<4)|(0x1<<5));// avilitamos los pines 
	GPIOB->DEN&=~((0x1<<4)|(0x1<<5));// 
	GPIOE->AMSEL|=(0x1<<4)|(0x1<<5);// utilizamos funcion alternativa
	GPIOB->AMSEL|=(0x1<<4)|(0x1<<5);//
	
	//Configuracion ADC principal
	
	ADC0->ACTSS&=~(0xF);//desactivamos secuenciadores durantes la configuracion
	ADC0->EMUX=0; //para trigger por sofware (default)
	
	//Configuracion del sequenciador
	ADC0->SSMUX0=(0x8)|(0x9<<4)|(0xA<<8)|(0xB<<12);
	ADC0->SSCTL0=(0x1<<14)|(0x1<<13);//Final de secuencia en muestra 3, y genera interrupcion
	//Desenmacaramos interrupcion por secuenciador 0
	ADC0->IM|=(0x1<<0);
	ADC0->ACTSS|=(0x1<<0);//activamos secuenciador 0
}

void ADC0SS0_Handler(){
	int i;
	ADC0->ISC=(0x1<<0);//Limpiamos interrupcion por secuenciador 0
	for(i=0;i<4;i++){
		if((ADC0->SSFSTAT0&(0x1<<8))){
			 break;
		}
		ADC_samples[i]=ADC0->SSFIFO0;
	}
	if(((ADC0->SSFSTAT0&(0x1<<8))!=0)&&i==4){
			ADC_sampleOk=1;
	}else{
		  ADC_sampleOk=0;
	}
	ADC_sampleEnd=1;
}

#include "board_tm4c123gxl.h"
#include "delay.h"
#include "TM4C123.h"                    // Device header



void start_ADC(void);

int ADC_samples[4];
int ADC_sampleOk=0;
int ADC_sampleEnd=1;
int a=0;


int main(){
    void adc_init(void);
	ADC_samples[0]=0;
	ADC_samples[1]=0;
	ADC_samples[2]=0;
	ADC_samples[3]=0;
	
	adc_init();
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

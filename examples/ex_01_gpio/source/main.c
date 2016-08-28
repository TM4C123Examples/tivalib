#include "TM4C123.h"                    // Device header

void delay_ms(void);

int main(){
  SYSCTL->RCGCGPIO|=(0x01)<<5;	//0x01
	GPIOF->DEN|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
	GPIOF->DIR|=(0x1<<1)|(0x1<<2)|(0x1<<3);//Activamos pin F1 F2 F3
	while(1){
			GPIOF->DATA=0xF;
		  delay_ms();
		  GPIOF->DATA=0x0;
		  delay_ms();
	}
	return 0;
}


void delay_ms(void){
	int a=0;
	for(int i=0; i<500000; i++){
		 a++;
	}
}

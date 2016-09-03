#include "TM4C123.h" // Device header
#include "spi_tm4c.h"

void spi_init(void){
    SYSCTL->RCGCGPIO|=0x1;//Turn on GPIOA
    SYSCTL->RCGCSSI|=0x1;//Turn on SSI0
    // PA2(SSI0CLK) PA3(SSI0Fss) PA4(SSI0Rx) PA5(SSI0Tx)
    GPIOA->DEN|=((0x1<<2)|(0x1<<3)|(0x1<<5));
    GPIOA->DIR|=((0x1<<2)|(0x1<<3)|(0x1<<5));
    GPIOA->PUR|=((0x1<<2)|(0x1<<3));
    GPIOA->PDR|=((0x1<<5));
    GPIOA->AFSEL|=((0x1<<2)|(0x1<<3)|(0x1<<5));
    GPIOA->PCTL&=~((0xF<<8)|(0xF<<12)|(0xF<<20));
    GPIOA->PCTL|=((0x2<<8)|(0x2<<12)|(0x2<<20));

    //configure for Freescale SPI Format (Single Transfer) with SPO=0 and SPH=0
    //For master operations, set the SSICR1 register to 0x0000.0000.
    SSI0->CR1=0;//bit 1 SSE: This bit must be cleared before any control registers are reprogrammed.
    //Configure the SSI clock source by writing to the SSICC register.
    SSI0->CC=(0x0<<0);//3:0 CS SSI Baud Clock Source = 0x0 System clock
    //Configure the clock prescale divisor by writing the SSICPSR register
    //BR=SysClk/(CPSDVSR * (1 + SCR))
    //where CPSDVSR is an even value from 2-254 programmed in the
    //SSICPSR register, and SCR is a value from 0-255.
    //BR=50MHz/(2*(1+9))=2.5MHz    (if SysClk=80MHz  then BR=4MHz)
    SSI0->CPSR=(0x2<<0);//7:0 CPSDVSR SSI Clock Prescale Divisor = 0x2
    SSI0->CR0=0;
    SSI0->CR0=((0x9<<8)| //15:8 SCR SSI Serial Clock Rate = 0x9
        (0x0<<7)|//7 SPH SSI Serial Clock Phase = 0x0 Data is captured on the first clock edge transition
        (0x0<<6)|//6 SPO SSI Serial Clock Polarity = 0x0 A steady state Low value is placed on the SSInClk pin.
        (0x0<<4)|//5:4 FRF SSI Frame Format Select = 0x0 Freescale SPI Frame Format
        (0xF<<0));//3:0 DSS  SSI Data Size Select = 0xF 16-bit data
    //Enable the SSI by setting the SSE bit in the SSICR1 register
    SSI0->CR1|=(0x1<<1);//1 SSE SSI Synchronous Serial Port Enable = 0x1 SSI operation is enabled

}
void spi_write16(unsigned short data){
    SSI0->DR=(0x7<<12)|(data&0xFFF);
}

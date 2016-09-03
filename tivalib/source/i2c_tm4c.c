#include "TM4C123.h"                    // Device header
#include "i2c_tm4c.h"

int i2c_isBusy(void);

void i2c_init(void){
    SYSCTL->RCGCGPIO|=0x1<<1;//Turn on GPIOB (for I2C0)
    SYSCTL->RCGCI2C|=0x1;//Turn on I2C0

    //configure B2(SCL) and B3(SDA) for I2C signals
    GPIOB->DEN|=(0x1<<2)|(0x1<<3); //digital type
    GPIOB->PUR|=(0x1<<2)|(0x1<<3); //pull ups
    GPIOB->ODR|=(0x1<<3); //open-drain output (only on SDA pin)
    GPIOB->AFSEL|=(0x1<<2)|(0x1<<3);//alternate functions
    GPIOB->PCTL|=(0x3<<8)|(0x3<<12);//pins controlled by I2C0

    I2C0->MCR=0x10;//I2C module in master mode
    I2C0->MTPR=0x18;//clock configuration 50MHz to 100KHz(standard speed)
}

void i2c_sendData(unsigned char address_7b,unsigned char data){
    I2C0->MSA=(address_7b<<1)|(0x0);//write to address uC->slave
    I2C0->MDR=data;
    I2C0->MCS=0x7;//single master transmit (STOP START RUN)
    while(i2c_isBusy());
}

unsigned char i2c_readData(unsigned char address_7b,unsigned char regAddress){
    I2C0->MSA=(address_7b<<1)|(0x0);//write uC->slave
    I2C0->MDR=regAddress;
    I2C0->MCS=0x3;//single master transmit (START RUN)
    while(i2c_isBusy());
    I2C0->MSA=(address_7b<<1)|(0x1);//read uC<-slave
    I2C0->MCS=0x7;//single master receive (STOP START RUN)
    while(i2c_isBusy());
    return I2C0->MDR;
}

void i2c_sendPacket(unsigned char  address_7b,unsigned char  *pData,int nData){
    int i;
    if(nData>0){
        I2C0->MSA=(address_7b<<1)|(0x0);//write to address uC->slave
        I2C0->MDR=pData[0];
        I2C0->MCS=(nData>1)?0x3:0x7;//single master transmit (START RUN)/(STOP START RUN)
        while(i2c_isBusy());
        for(i=1; i<(nData-1); i++){
            I2C0->MDR=pData[i];
            I2C0->MCS=0x1;//single master transmit (RUN)
            while(i2c_isBusy());
        }
        if(nData>1){
            I2C0->MDR=pData[nData-1];
            I2C0->MCS=0x5;//single master transmit (STOP RUN)
            while(i2c_isBusy());
        }
    }
}

void i2c_readPacket(unsigned char  address_7b,unsigned char regAddress,
        unsigned char  *pData,int nData){
    if(nData>0){
        //Write register Address
        I2C0->MSA=(address_7b<<1)|(0x0);//write uC->slave
        I2C0->MDR=regAddress;
        I2C0->MCS=0x3;//single master transmit (START RUN)
        while(i2c_isBusy());
        //read first byte
        I2C0->MSA=(address_7b<<1)|(0x1);//read uC<-slave
        I2C0->MCS=(nData>1)?0xB:0x7;//single master transmit (ACK START RUN)/(STOP START RUN)
        while(i2c_isBusy());
        pData[0] = I2C0->MDR;
        //This only executes if nData >= 3
        for(int i=1; i<(nData-1); i++){
                I2C0->MCS=0x9;//single master transmit (RUN)
                while(i2c_isBusy());
                pData[i] = I2C0->MDR;
        }
        // only  executes if nData >= 2
        if(nData>1){
            I2C0->MCS=0x5;//single master transmit (STOP RUN)
            while(i2c_isBusy());
            pData[nData-1] = I2C0->MDR;
        }
    }
}

int i2c_isBusy(void){
    return (((I2C0->MCS)&(0x1<<0))>>0);//return busy bit
}


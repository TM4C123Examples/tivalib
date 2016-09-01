#ifndef _I2C_TM4C_H
#define _I2C_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif

void i2c_config(void);
void i2c_sendData(unsigned char  address_7b,unsigned char data);
unsigned char i2c_readData(unsigned char address_7b,unsigned char regAddress);
void i2c_sendPacket(unsigned char  address_7b,unsigned char  *pData,int nData);
int i2c_isBusy(void);
void dac_output(short val);
void dac_config(void);

#ifdef __cplusplus
}
#endif

#endif /* _I2C_TM4C_H */

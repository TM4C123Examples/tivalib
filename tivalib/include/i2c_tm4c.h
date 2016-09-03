#ifndef _I2C_TM4C_H
#define _I2C_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif

void i2c_init(void);
void i2c_sendData(unsigned char  address_7b,unsigned char data);
unsigned char i2c_readData(unsigned char address_7b,unsigned char regAddress);
void i2c_sendPacket(unsigned char  address_7b,unsigned char  *pData,int nData);
void i2c_readPacket(unsigned char  address_7b,unsigned char regAddress, unsigned char  *pData,int nData);

#ifdef __cplusplus
}
#endif

#endif /* _I2C_TM4C_H */

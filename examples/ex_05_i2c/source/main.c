#include "delay.h"
#include "i2c_tm4c.h"
#include "uart_tm4c.h"
#include "serial_stdio.h"
#include "serial_tm4c.h"
#include <stdint.h>

#define MPU6050_ADDRESS 0x68

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_GYRO_XOUT_L 0x44
#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46
#define MPU6050_GYRO_ZOUT_H 0x37
#define MPU6050_GYRO_ZOUT_L 0x48


void mpu6050_init(void);
int16_t mpu6050_readAccel(char axis);

int main(){
    int data_x, data_y, data_z;
    UART0_init(9600);
    mpu6050_init();

    serial_printf(serial_uart0,"\nSystem ready\n");

    while(1){
        data_x = mpu6050_readAccel('x');
        data_y = mpu6050_readAccel('y');
        data_z = mpu6050_readAccel('z');
        serial_printf(serial_uart0,"x = %d, y = %d, z = %d\n",data_x, data_y, data_z);
        delay_ms(500);
    }
}

void mpu6050_init(void){
    unsigned char confpacket[] = {0x6B,0x00};
    i2c_init();
    i2c_sendPacket(MPU6050_ADDRESS,confpacket,2);
}

int16_t mpu6050_readAccel(char axis){
    int16_t accel_reading = 0;
    unsigned char axis_data_h;
    unsigned char axis_data_l;
    unsigned char axis_address_h;

    if((axis >= 'x') && (axis <= 'z')){
        axis_address_h = MPU6050_ACCEL_XOUT_H + (axis - 'x')*2;
        axis_data_h = i2c_readData(MPU6050_ADDRESS,axis_address_h);
        axis_data_l = i2c_readData(MPU6050_ADDRESS,axis_address_h+1);
        accel_reading = (axis_data_h << 8) | (axis_data_l);
    }
    return accel_reading;
}

int16_t mpu6050_readGyro(char axis){
    int16_t gyro_reading = 0;
    unsigned char axis_data_h;
    unsigned char axis_data_l;
    unsigned char axis_address_h;

    if((axis >= 'x') && (axis <= 'z')){
        axis_address_h = MPU6050_GYRO_XOUT_H + (axis - 'x')*2;
        axis_data_h = i2c_readData(MPU6050_ADDRESS,axis_address_h);
        axis_data_l = i2c_readData(MPU6050_ADDRESS,axis_address_h+1);
        gyro_reading = (axis_data_h << 8) | (axis_data_l);
    }
    return gyro_reading;
}

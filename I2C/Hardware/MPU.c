#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU_Reg.h"



void MPU_write(uint8_t slave_address, uint8_t reg_address ,uint8_t data){
	myI2C_start();
	myI2C_send(slave_address);
	myI2C_receiveack();
	myI2C_send(reg_address);
	myI2C_receiveack();
	myI2C_send(data);
	myI2C_receiveack();
	myI2C_stop();
}

void MPU6050_Init(uint8_t slave_address)
{
	myI2C_init();
	MPU_write(slave_address,MPU6050_PWR_MGMT_1, 0x01);
	MPU_write(slave_address,MPU6050_PWR_MGMT_2, 0x00);
	MPU_write(slave_address,MPU6050_SMPLRT_DIV, 0x09);
	MPU_write(slave_address,MPU6050_CONFIG, 0x06);
	MPU_write(slave_address,MPU6050_GYRO_CONFIG, 0x18);
	MPU_write(slave_address,MPU6050_ACCEL_CONFIG, 0x18);
}


uint8_t MPU_read(uint8_t slave_address, uint8_t reg_address){
	uint8_t data;
	myI2C_start();
	myI2C_send(slave_address);
	myI2C_receiveack();
	myI2C_send(reg_address);
	myI2C_receiveack();

	
	myI2C_start();
	myI2C_send(slave_address|0x01);
	myI2C_receiveack();
	data = myI2C_read();
	myI2C_sendack(1);
	myI2C_stop();
	return data;
}


void MPU_getdata(uint8_t slave_address, int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;
	
	DataH = MPU_read(slave_address, MPU6050_ACCEL_XOUT_H);
	DataL = MPU_read(slave_address, MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH<<8) | DataL;
	
	DataH = MPU_read(slave_address, MPU6050_ACCEL_YOUT_H);
	DataL = MPU_read(slave_address, MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU_read(slave_address, MPU6050_ACCEL_ZOUT_H);
	DataL = MPU_read(slave_address, MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU_read(slave_address, MPU6050_GYRO_XOUT_H);
	DataL = MPU_read(slave_address, MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU_read(slave_address, MPU6050_GYRO_YOUT_H);
	DataL = MPU_read(slave_address, MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU_read(slave_address, MPU6050_GYRO_ZOUT_H);
	DataL = MPU_read(slave_address, MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;

}




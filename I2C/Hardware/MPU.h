#ifndef  __MPU
#define	__MPU


void MPU6050_Init(uint8_t slave_address);

void MPU_write(uint8_t slave_address, uint8_t reg_address ,uint8_t data);

uint8_t MPU_read(uint8_t slave_address, uint8_t reg_address);
void MPU_getdata(uint8_t slave_address, int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
#endif

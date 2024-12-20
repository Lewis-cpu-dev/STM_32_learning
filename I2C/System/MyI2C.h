#ifndef __MyI2C
#define __MyI2C

#define SCL_port GPIOB
#define SCL_pin GPIO_Pin_10
#define SDA_port GPIOB
#define SDA_pin GPIO_Pin_11


void SCL_w(uint8_t x);
void SDA_w(uint8_t x);
uint8_t SDA_r(void);
void myI2C_init(void);
void myI2C_start(void);
void myI2C_stop(void);
void myI2C_send(uint8_t data);
uint8_t myI2C_read(void);
void myI2C_sendack(uint8_t ack);
uint8_t myI2C_receiveack(void);


#endif

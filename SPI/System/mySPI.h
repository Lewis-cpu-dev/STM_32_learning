#ifndef __SPI
#define __SPI

void write_MO(uint8_t bit);

void write_CS(uint8_t bit);
void write_CLK(uint8_t bit);
uint8_t read_MI(void);

void mySPI_init(void);
void MySPI_Start(void);
void MySPI_Stop(void);

uint8_t mySPI_swapdata(uint8_t senddata);


#endif

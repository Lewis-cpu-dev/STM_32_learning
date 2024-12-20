#ifndef __W25_H
#define __W25_H

void W25Q64_Init(void);
void read_device_id(uint8_t *MID, uint16_t *DID);
void write_page_program(uint32_t address, uint8_t *array, uint16_t count);
void W25Q64_SectorErase(uint32_t Address);
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);


#endif


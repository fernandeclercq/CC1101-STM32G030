/**
 * @file spi.h
 * @author Fernando Declercq
 * @brief 
 * @version 0.1
 * @date 2024-03-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SPI_H
#define SPI_H

#include "system.h"


void spi1_init(void);
void spi1_transmit_bytes(uint8_t * data, uint32_t size);
void spi1_receive_bytes(uint8_t * data, uint32_t size);
void spi1_receive_byte(uint8_t * data);
void spi1_transmit_byte(uint8_t data);
uint8_t spi1_read_miso(void);
void spi1_cs_enable(void);
void spi1_cs_disable(void);

#endif /* SPI_H */

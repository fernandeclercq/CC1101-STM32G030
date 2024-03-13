#ifndef SPI_H
#define SPI_H

#include "system.h"

void spi1_gpio_init(void);
void spi1_config_init(void);

void spi1_transmit_bytes(uint8_t * data, uint32_t size);
void spi1_transmit_byte(uint8_t data);

void spi1_receive_bytes(uint8_t * data, uint32_t size);
void spi1_receive_byte(uint8_t * data);

void cs_enable(void);
void cs_disable(void);


#endif /* SPI_H */

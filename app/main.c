/**
 * @file main.c
 * @author Fernando Declercq
 * @brief 
 * @version 0.1
 * @date 2024-03-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "system.h"
#include "uart.h"
#include "cc1101.h"
#include "spi.h"

cc1101_handle_t cc1101_handle;


void SysTick_Handler(void);


uint32_t timestamp = 0;
uint32_t time_passed = 0;

int main(void)
{

    system_init();

    UART1_Init();

    LL_SYSTICK_EnableIT();

    LOG_DEBUG("System Restart\n");


    cc1101_handle.delay_ms = delay_ms;
    cc1101_handle.spi_read_byte = spi1_receive_byte;
    cc1101_handle.spi_write_byte = spi1_transmit_byte;


    cc1101_init(&cc1101_handle);

    while (1)
    {
        LOG_DEBUG("Hello World\n");
        delay_ms(500);
    }
}

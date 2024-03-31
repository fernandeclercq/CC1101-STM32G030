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

//cc1101_handle_t  * cc1101_handle;


void SysTick_Handler(void);


uint32_t timestamp = 0;
uint32_t time_passed = 0;


#include <assert.h>

int main(void)
{

    system_init();

    UART1_Init();

    LL_SYSTICK_EnableIT();

    LOG_DEBUG("System Restart\n");

    spi1_init();

    cc1101_init(spi1_receive_byte, spi1_transmit_byte, delay_ms, spi1_cs_enable, spi1_cs_disable, spi1_read_miso);


    while (1)
    {
        LOG_DEBUG("Hello World\n");
        read_test();
        delay_ms(500);
    }
}

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


void SysTick_Handler(void);


uint32_t timestamp = 0;
uint32_t time_passed = 0;

int main(void)
{

    system_init();

    UART1_Init();

    LL_SYSTICK_EnableIT();

    LOG_DEBUG("System Restart\n");

    while (1)
    {
        LOG_DEBUG("Hello World\n");
        delay_ms(500);
    }
}

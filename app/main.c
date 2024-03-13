/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "system.h"
#include "uart.h"
//#include "cc1101.h"

void SysTick_Handler(void);


uint32_t timestamp = 0;
uint32_t time_passed = 0;

int main(void)
{

    SystemClock_Config();

    UART1_Init();

    LL_SYSTICK_EnableIT();

    printf("System Restart\n");

    while (1)
    {
        printf("Hello World\n");
        delay_us(5000);
    }
}


void SysTick_Handler(void)
{
    // Update Systick Counter (1ms base)
    systick_counter++;
}

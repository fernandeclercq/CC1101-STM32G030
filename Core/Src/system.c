/**
 * @file system.c
 * @author Fernando Declercq (Fernando.Declercq@onedge.dev)
 * @brief System Source File
 * @version 0.1
 * @date 2023-12-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "system.h"

volatile uint32_t systick_counter;


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  LL_Init1msTick(CLOCK_SPEED_HZ);

  

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(CLOCK_SPEED_HZ);
}


/**
 * @brief Delay in Microseconds by using NOPs
 * The define "MCU_CLOCK_SPEED" has to be defined in the CMakeLists.txt for this to work
 *
 * @param delay_in_us A unsigned int of 32-bit
 */
void delay_us(uint32_t delay_in_us)
{
    uint32_t i = 0;

    // MCU_CLOCK_CYCLE_NS = 63 if 16MHz MCU Clock Speed
    for (i = 0; (MCU_CLOCK_CYCLE_NS * i) <= (delay_in_us * 1000); i++)
    {
        __NOP();
    }
}
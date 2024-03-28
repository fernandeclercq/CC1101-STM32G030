/**
 * @file system.c
 * @author Fernando Declercq
 * @brief System Source File
 * @version 0.1
 * @date 2023-12-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "system.h"

volatile uint32_t systick_counter;
void SystemClock_Config(void);
void timer3_init();
void SysTick_Handler(void);


void system_init()
{
  SystemClock_Config();
  timer3_init();
}


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


void timer3_init()
{
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3); // Enable Clock for TIM3 PERIPHERAL

    LL_TIM_SetPrescaler(TIM3, (1600 - 1)); // 16 000 000 / 1 600 = 10 000 Hz

    LL_TIM_SetAutoReload(TIM3, (10 - 1)); // 100 / 10 000 = 0.1 (1ms)

    LL_TIM_SetCounter(TIM3, 0); // Reset Counter
}

void delay_ms(uint32_t delay)
{  
    uint32_t counter;
    for(counter = 0; counter < delay; counter++)
    {
        LL_TIM_SetCounter(TIM3, 0); // Reset Counter

        LL_TIM_EnableCounter(TIM3); // Enable Timer

        while(1){
            if((LL_TIM_IsActiveFlag_UPDATE(TIM3)))
            {
                break;
            }
        }
        LL_TIM_ClearFlag_UPDATE(TIM3);
    }

    LL_TIM_SetCounter(TIM3, 0); // Reset Counter

    LL_TIM_DisableCounter(TIM3);

}

void SysTick_Handler(void)
{
    // Update Systick Counter (1ms base)
    systick_counter++;
}
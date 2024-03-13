/**
 * @file system.h
 * @author Fernando Declercq (Fernando.Declercq@onedge.dev)
 * @brief System Header File
 * @version 0.1
 * @date 2023-12-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SYSTEM_H

#define SYSTEM_H

/**
 * \cond
 * Hide includes from Doxygen
*/

/* Header file for STM32g030xx MCU family */
#include "stm32g030xx.h"
/*****************************************/

/* Standard Library Includes */
#include <string.h>
#include <stdint.h>
#include <stdio.h>
/*****************************/


/* LL Drivers for STM32g0xx */

#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
//#include "stm32g0xx_ll_pwr.h"
//#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

// #include "stm32g0xx_ll_adc.h"

// #include "stm32g0xx_ll_comp.h"

// #include "stm32g0xx_ll_crc.h"
// #include "stm32g0xx_ll_crs.h"
// //#include "stm32g0xx_ll_dac.h"

// #include "stm32g0xx_ll_dmamux.h"


// #include "stm32g0xx_ll_i2c.h"
// #include "stm32g0xx_ll_iwdg.h"
// #include "stm32g0xx_ll_lptim.h"
// #include "stm32g0xx_ll_lpuart.h"


// #include "stm32g0xx_ll_rng.h"
// #include "stm32g0xx_ll_rtc.h"
#include "stm32g0xx_ll_spi.h"

#include "stm32g0xx_ll_tim.h"
// #include "stm32g0xx_ll_ucpd.h"


// #include "stm32g0xx_ll_wwdg.h"
/******************************/

/**
 * \endcond
*/

/***** Extra Includes *****/
//#include "project_config.h"

/**************************/


/**
 * @def CLOCK_SPEED_HZ
 * Defines the Microcontroller Clock Speed in Hertz (Hz)
 */
#define CLOCK_SPEED_HZ     MCU_CLOCK_SPEED_HZ

/**
 * @fn SystemClock_Config
 * @brief Configures the System Clock to 16MHz.
 */
void SystemClock_Config(void);


/**
 * @fn delay_us
 * 
 * @param delay_in_us 
 */
void delay_us(uint32_t delay_in_us);

extern volatile uint32_t systick_counter;


#endif /* SYSTEM_H */

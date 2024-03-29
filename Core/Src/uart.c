/**
 * @file uart.c
 * @author Fernando Declercq
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "uart.h"




int __io_putchar(int ch)
{
	//uart1_write(ch);
  UART1_send_byte((uint8_t)ch);
	return ch;
}

void UART1_send_bytes(const uint8_t * buffer, size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    UART1_send_byte(buffer[i]);
  }
}

void UART1_send_byte(uint8_t ch)
{
  
  while(!(LL_USART_IsActiveFlag_TXE_TXFNF(USART1))){}

  LL_USART_TransmitData8(USART1, ch);

}

void UART1_Init(void)
{
    /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  /**USART1 GPIO Configuration
  PB7   ------> USART1_RX
  PB6   ------> USART1_TX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART1);
  LL_USART_ConfigAsyncMode(USART1);

  /* USER CODE BEGIN WKUPType USART1 */

  /* USER CODE END WKUPType USART1 */

  LL_USART_Enable(USART1);

  /* Polling USART1 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
  {
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
}


void UART1_RXNE_IT_Init(void)
{
	__disable_irq();
	LL_USART_Disable(USART1);

	LL_USART_EnableIT_RXNE_RXFNE(USART1);

  LL_USART_DisableIT_IDLE(USART1);

	NVIC_EnableIRQ(USART1_IRQn);

	LL_USART_Enable(USART1);

	/* Polling USART1 initialisation */
	while ((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
	{
	}
	__enable_irq();
}


void UART1_RX_IT_IDLE(void)
{
	__disable_irq();
	LL_USART_Disable(USART1);

	LL_USART_EnableIT_IDLE(USART1);

	NVIC_EnableIRQ(USART1_IRQn);

	LL_USART_Enable(USART1);

	/* Polling USART1 initialisation */
	while ((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
	{
	}
	__enable_irq();
}

void UART1_RX_IT_CM(char char_to_match)
{
	__disable_irq();
	LL_USART_Disable(USART1);

	LL_USART_DisableDirectionRx(USART1);

	//LL_USART_EnableIT_IDLE(USART1);

	USART1->CR2 |= (uint32_t)(char_to_match << 24);

	USART1->CR2 |= (1U<<4U);

	NVIC_EnableIRQ(USART1_IRQn);

	LL_USART_EnableDirectionRx(USART1);

	LL_USART_Enable(USART1);

	/* Polling USART1 initialisation */
	while ((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
	{
	}
	__enable_irq();
}

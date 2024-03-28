/**
 * @file uart.h
 * @author Fernando Declercq
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef UART_H

#define UART_H

#include "system.h"

void UART1_Init(void);
void UART1_RX_IT_CM(char char_to_match);
void UART1_RX_IT_IDLE(void);
void UART1_RXNE_IT_Init(void);

void UART1_send_byte(uint8_t ch);
void UART1_send_bytes(const uint8_t * buffer, size_t len);




#endif /* UART_H */

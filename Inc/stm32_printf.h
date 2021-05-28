/*
 * stm32_printf.h
 * Created on: 2019/08/23
 *     Author: hajime
 */

#ifndef UARTPRINTF_H_
#define UARTPRINTF_H_

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void stm32_printf_init(UART_HandleTypeDef *huart);
void stm32f3_puts(uint8_t USART_TX_data[]);
void stm32_printf(const char *format, ...);

#ifdef __cplusplus
};
#endif

#endif /* UARTPRINTF_H_ */

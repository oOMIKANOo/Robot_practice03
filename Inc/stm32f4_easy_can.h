/* 
 * File:    stm32f4_easy_can.h
 * version: ver02.01 (2019/03/26)
 * Author:  hajime
 *
 * Created on 2019/03/26, 21:42
 */

#ifndef STM32F4_EASY_CAN_H_
#define STM32F4_EASY_CAN_H_

#include "stm32f3xx_hal.h"

//#define DEFAULT_ACCEPTANCE_FILTER  0X000	// 11�r�b�g(0X000�`0X7FF)
//#define DEFAULT_FILTER_MASK        0b11111	// 11�r�b�g(0X000�`0X7FF)

void stm32f4_easy_can_init(CAN_HandleTypeDef *hcan, unsigned int default_acceptance_filter, unsigned int default_filter_mask);
void stm32f4_easy_can_get_receive_message(int *receive_id, int *receive_dlc, unsigned char receive_message[]);
int stm32f4_easy_can_transmit_message(int transmit_id, int transmit_dlc, const unsigned char transmit_message[]);
void stm32f4_easy_can_interrupt_handler(void); // ��M���荞�݃n���h��(��M���荞�݂���������ƌĂ΂��D�����Œ�`����K�v������)

#endif /* STM32F4_EASY_CAN_H_ */

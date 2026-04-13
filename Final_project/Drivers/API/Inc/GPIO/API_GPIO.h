/*
 * API_GPIO.h
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_GPIO_API_GPIO_H_
#define API_INC_GPIO_API_GPIO_H_

#include "stm32f4xx_hal.h"
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define MODE_Pin GPIO_PIN_10
#define MODE_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define XLAT_Pin GPIO_PIN_4
#define XLAT_GPIO_Port GPIOB
#define BLANK_Pin GPIO_PIN_5
#define BLANK_GPIO_Port GPIOB

void GPIO_Init(void);

#endif /* API_INC_GPIO_API_GPIO_H_ */

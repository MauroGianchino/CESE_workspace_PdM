

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"


UART_HandleTypeDef huart2;
uint32_t timeout = 100;
char newLine[] = "\n\r";

bool uartInit(){



	uint8_t *data;

	char buffer[12]; // Suficiente para 10 dígitos + terminador nulo '\0'


	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	 if (HAL_UART_Init(&huart2) != HAL_OK)
	 {
	   //Error_Handler();
	   return false;
	 }
	 else{

		 snprintf(buffer, sizeof(buffer), "%u", huart2.Init.BaudRate);

		 HAL_UART_Transmit(&huart2, (uint8_t *)buffer, 6, timeout);
		 HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);

		 memset(buffer, 0, sizeof(buffer));

		 snprintf(buffer, sizeof(buffer), "%u", huart2.Init.WordLength);

		 HAL_UART_Transmit(&huart2, (uint8_t *)buffer, 6, timeout);
		 HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);


		 //aca se imprimen todos los parametros. Falta pasarlos a CHAR. se usara funcion en string.h?

		 return true;
	 }

}

void uartSendString(uint8_t * pstring){


	HAL_UART_Transmit(&huart2, pstring, sizeof(pstring), timeout);
	HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);

}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Transmit(&huart2, pstring, size, timeout);
	HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);

}

void uartReceiveStringSize(uint8_t * pstring, uint16_t size){



}

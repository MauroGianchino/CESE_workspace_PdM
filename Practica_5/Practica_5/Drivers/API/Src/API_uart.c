/*
 * API_uart.c
 *
 *  Created on: 03 apr 2026
 *      Author: magian
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"


UART_HandleTypeDef huart2;

static uint32_t timeout = 100;

static char newLine[] = "\n\r";

#define UART_MAX_SIZE 256
#define UART_MIN_SIZE 1

bool uartInit(void){

	char initial[]="UART inicializada"; // Suficiente para 10 dígitos + terminador nulo '\0'
	char wordLength[] = "Wordlength: 8 bits";
	char baudRate[] = "Baudrate: 115200";
	char paridad[] = "Paridad: sin paridad";

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

		 //escribo: UART inicializada
		 HAL_UART_Transmit(&huart2, (uint8_t *)initial, sizeof(initial), timeout);
		 HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);
		 //----------------------
		 //BAUDRATE
		 HAL_UART_Transmit(&huart2, (uint8_t *)baudRate, sizeof(baudRate), timeout);

		 HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);

		 //----------------------
		 //WORDLENGTH

		HAL_UART_Transmit(&huart2, (uint8_t *)wordLength, sizeof(wordLength), timeout);

		HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);
		 //----------------------
		//PARIDAD
		HAL_UART_Transmit(&huart2, (uint8_t *)paridad, sizeof(paridad), timeout);

		HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);


		 return true;
	 }

}

void uartSendString(uint8_t * pstring){
	if (pstring == NULL) {
	        return;
	}


	HAL_UART_Transmit(&huart2, pstring, strlen((char *)pstring), timeout);
	HAL_UART_Transmit(&huart2, (uint8_t *)newLine , 2, timeout);

}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	if (pstring == NULL) {
	   return;
	}

	uint32_t len = strlen((char*)pstring);

	if (len < UART_MIN_SIZE || len > UART_MAX_SIZE){
		return;
	}

	if(HAL_UART_Transmit(&huart2, pstring, size, 0)!= HAL_OK){
		return;
	}



}

bool uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	if (pstring == NULL) {
		   return false;
	}

	uint32_t len = strlen((char*)pstring);

	if (len < UART_MIN_SIZE || len > UART_MAX_SIZE){
		return false;
	}

	if(HAL_UART_Receive(&huart2, pstring, size, timeout) != HAL_OK){
		return false;
	}
	else{
		return true;
	}


}

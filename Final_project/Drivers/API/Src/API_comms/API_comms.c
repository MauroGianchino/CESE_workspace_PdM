/*
 * API_comms.c
 *
 *  Created on: 14 abr 2026
 *      Author: Mauro
 */

#include "API_comms.h"


I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;

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


void I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}



void SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

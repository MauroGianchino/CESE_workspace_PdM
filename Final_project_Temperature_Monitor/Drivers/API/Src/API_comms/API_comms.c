/*
 * API_uart.c
 *
 *  Created on: 03 apr 2026
 *      Author: magian
 */

#include "API_comms.h"

I2C_HandleTypeDef hi2c3;

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

	if (pstring == NULL)
	{
		return;
	}
	if (size == 0)
	{
		return;
	}

	uint32_t len = strlen((char*)pstring);

	if (len < UART_MIN_SIZE || len > UART_MAX_SIZE)
	{
		return;
	}

	if(HAL_UART_Transmit(&huart2, pstring, size, 0)!= HAL_OK)
	{
		return;
	}



}

bool uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	if (pstring == NULL)
	{
		return false;
	}
	if (size == 0)
	{
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

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
void I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
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
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
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

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

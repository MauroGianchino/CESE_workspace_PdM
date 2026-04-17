/*
 * TLC5923_port.c
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */

#include "TLC5923_port.h"

extern SPI_HandleTypeDef hspi2;

bool writeData(uint8_t*data)
{
	HAL_StatusTypeDef status;

	status = HAL_SPI_Transmit(&hspi2, data, 1, HAL_MAX_DELAY); //envio la data de 16 bits

	if (status == HAL_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}



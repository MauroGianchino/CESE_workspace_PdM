/*
 * API_TLC5923.c
 *
 *  Created on: 9 abr 2026
 *      Author: Mauro
 */


#include "API_TLC5923.h"


void setBlank()
{
	HAL_GPIO_WritePin(GPIOB, BLANK_Pin, GPIO_PIN_SET);
}

void resetBlank()
{
	HAL_GPIO_WritePin(GPIOB, BLANK_Pin, GPIO_PIN_RESET);
}


void setModeDC()
{
	HAL_GPIO_WritePin(GPIOA, MODE_Pin, GPIO_PIN_SET);
}

void setModeOnOff()
{
	HAL_GPIO_WritePin(GPIOA, MODE_Pin, GPIO_PIN_RESET);
}

bool setOutputs(uint16_t outputs)
{
	HAL_GPIO_WritePin(GPIOB, XLAT_Pin, GPIO_PIN_RESET);

	if(writeData((uint8_t*)&outputs) == true)
	{
		//HAL_Delay(1);

		HAL_GPIO_WritePin(GPIOB, XLAT_Pin, GPIO_PIN_SET);

		//HAL_Delay(1);

		HAL_GPIO_WritePin(GPIOB, XLAT_Pin, GPIO_PIN_RESET);

		return true;
	}
	else
	{
		return false;
	}


}

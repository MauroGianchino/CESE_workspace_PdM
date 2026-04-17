/*
 * API_TLC5923.c
 *
 *  Created on: 9 abr 2026
 *      Author: Mauro
 */


#include "API_TLC5923.h"


void TLC5923_disableOutputs()
{
	HAL_GPIO_WritePin(GPIOB, BLANK_Pin, GPIO_PIN_SET);
}

void TLC5923_enableOutputs()
{
	HAL_GPIO_WritePin(GPIOB, BLANK_Pin, GPIO_PIN_RESET);
}


void TLC5923_setModeDC()
{
	HAL_GPIO_WritePin(GPIOA, MODE_Pin, GPIO_PIN_SET);
}

void TLC5923_setModeOnOff()
{
	HAL_GPIO_WritePin(GPIOA, MODE_Pin, GPIO_PIN_RESET);
}

bool TLC5923_setOutputsOnOff(uint16_t outputs)
{
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);

	if(writeData((uint8_t*)&outputs) == true)
	{
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);

		return true;
	}
	else
	{
		return false;
	}


}

bool TLC5923_setOutputsDC(uint16_t outputs)
{
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);

	writeData((uint8_t*)&outputs);
	writeData((uint8_t*)&outputs);
	writeData((uint8_t*)&outputs);
	writeData((uint8_t*)&outputs);
	writeData((uint8_t*)&outputs);
	writeData((uint8_t*)&outputs);
	writeData((uint8_t*)&outputs);

	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);

	return true;



}

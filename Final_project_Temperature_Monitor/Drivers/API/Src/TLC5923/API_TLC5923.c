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

	if(writeData((uint8_t*)&outputs))
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

bool TLC5923_setOutputsDC(uint16_t *outputs)
{
	if (outputs == NULL)
	{
		return false;
	}
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);

	for (int i = 0; i < 7; i++) {
	        // Enviamos la dirección de cada elemento del arreglo
		if (!writeData((uint8_t*)&outputs[i])) {
	           return false; // Registramos si hubo algún fallo en el puerto
	    }
	}

	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);

	return true;

}

bool TLC5923_init()
{
	uint16_t outputsDC[7] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}; // todos los 112 bits en uno para setear la mayor intensidad en cada salida
	TLC5923_setModeDC(); //primero se setea en modo DC para configurar la intensidad en cada salida
	TLC5923_enableOutputs(); //se habilitan las salidas
	if(!TLC5923_setOutputsDC(outputsDC)) //se mandan los datos
	{
		return false;
	}
	TLC5923_setModeOnOff(); //se vuelve al modo ON/OFF

	return true;
}

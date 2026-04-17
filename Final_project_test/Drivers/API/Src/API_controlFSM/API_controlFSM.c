/*
 * API_controlFSM.c
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */


#include "API_controlFSM.h"


typedef enum{
	CONTROL_IDLE = 0,
	CONTROL_READ_TEMPERATURE,
	CONTROL_PROCESS,
	CONTROL_ERROR
} controlState_t;

static controlState_t statusControlFSM;

extern SPI_HandleTypeDef hspi2;

static delay_t delay;

static tick_t durationDelay = 1000; //1 segundo de tiempo base entre mediciones de temperatura

float temperature; //variable que guarda la temperatura leida

float maxTemp = 35; //variable que guarda el valor alto del rango de temperatura

float minTemp = 25; //variable que guarda  el valor bajo del rango de temperatura

float quantityLeds = 8; //cantidad de leds que se iluminan. variable que se usa apra el paso de temperatura dentro del rango

void controlInit(void){

	statusControlFSM = CONTROL_IDLE;
	uint16_t data0 = 0xFFFF;
	delayInit(&delay,durationDelay);
	TLC5923_setModeDC();
	TLC5923_enableOutputs();
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef status;
	status = HAL_SPI_Transmit(&hspi2, /*(i % 2 ? &data0 : &data1)*/(uint8_t*)&data0, 1, HAL_MAX_DELAY);
	status = HAL_SPI_Transmit(&hspi2, /*(i % 2 ? &data0 : &data1)*/(uint8_t*)&data0, 1, HAL_MAX_DELAY);
	status = HAL_SPI_Transmit(&hspi2, /*(i % 2 ? &data0 : &data1)*/(uint8_t*)&data0, 1, HAL_MAX_DELAY);
	status = HAL_SPI_Transmit(&hspi2, /*(i % 2 ? &data0 : &data1)*/(uint8_t*)&data0, 1, HAL_MAX_DELAY);
	status = HAL_SPI_Transmit(&hspi2, /*(i % 2 ? &data0 : &data1)*/(uint8_t*)&data0, 1, HAL_MAX_DELAY);
	status = HAL_SPI_Transmit(&hspi2, /*(i % 2 ? &data0 : &data1)*/(uint8_t*)&data0, 1, HAL_MAX_DELAY);
	status = HAL_SPI_Transmit(&hspi2, /*(i % 2 ? &data0 : &data1)*/(uint8_t*)&data0, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);
	TLC5923_setModeOnOff();
}


void controlPoll(void){


		switch(statusControlFSM){
		case CONTROL_IDLE:

			if(delayRead(&delay))
			{
				statusControlFSM = CONTROL_READ_TEMPERATURE;
			}

			break;
		case CONTROL_READ_TEMPERATURE:
			if(TMP117_readTemperature(&temperature))
			{

				statusControlFSM = CONTROL_PROCESS;
			}
			else
			{
				statusControlFSM = CONTROL_ERROR;
			}

			break;
		case CONTROL_PROCESS:
			controlProcess();
			statusControlFSM = CONTROL_IDLE;
			break;
		case CONTROL_ERROR:

			errorSequence();

			break;
		default:
			statusControlFSM = CONTROL_IDLE;
			break;
		}

}

void controlProcess()
{
	if((temperature > minTemp) && (temperature < maxTemp)) //si estoy dentro del rango
	{
		normalSequence();
	}
	if (temperature >= maxTemp)
	{
		//hotSequence();
	}
	if (temperature <= minTemp)
	{
		coldSequence();
	}

}

void normalSequence()
{
	float step = (maxTemp - minTemp)/quantityLeds;
	uint16_t data = 0b1111111111111111;

	if(temperature < (minTemp + step))
	{

		data = 0b1000000000000000;

	}
	else if(temperature < (minTemp + 2*step))
	{
		//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_RESET);
		data = 0b1010000000000000;
	}
	else if(temperature < (minTemp + 3*step))
	{
		data = 0b1010100000000000;
	}
	else if(temperature < (minTemp + 4*step))
	{
		data = 0b1010101000000000;
	}
	else if(temperature < (minTemp + 5*step))
	{
		data = 0b1010101001000000;
	}
	else if(temperature < (minTemp + 6*step))
	{
		data = 0b1010101001010000;
	}
	else if(temperature < (minTemp + 7*step))
	{
		data = 0b1010101001010100;
	}
	else if(temperature < (minTemp + 8*step))
	{
		data = 0b1010101001010101;
	}

	TLC5923_setOutputs(data);

}

void coldSequence()
{
	uint16_t data = 0b0101010110101010;

	if(TLC5923_setOutputs(data))
	{
		return;
	}
	else
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_SET);
	}
}

void errorSequence()
{

}

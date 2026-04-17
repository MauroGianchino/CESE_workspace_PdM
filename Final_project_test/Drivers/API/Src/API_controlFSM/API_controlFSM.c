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


static delay_t delayTemp;

static delay_t delayError;

static delay_t delayAlert;

static delay_t delayError;

static tick_t durationDelayTemp = 50; //1 segundo de tiempo base entre mediciones de temperatura

static tick_t durationDelayError = 2000; //1 segundo de tiempo base entre mediciones de temperatura

static tick_t durationDelayAlert = 300; //1 segundo de tiempo base entre mediciones de temperatura

uint8_t flagError = 0;

uint8_t flagAlert = 0;

float temperature; //variable que guarda la temperatura leida

static float maxTemp = 30; //variable que guarda el valor alto del rango de temperatura

static float minTemp = 20; //variable que guarda  el valor bajo del rango de temperatura

float quantityLeds = 8; //cantidad de leds que se iluminan. variable que se usa apra el paso de temperatura dentro del rango

void controlInit(void){

	statusControlFSM = CONTROL_IDLE;
	uint16_t data0 = 0xFFFF;
	delayInit(&delayTemp,durationDelayTemp);
	delayInit(&delayError,durationDelayError);
	delayInit(&delayAlert,durationDelayAlert);
	TLC5923_setModeDC();
	TLC5923_enableOutputs();
	TLC5923_setOutputsDC(data0);
	TLC5923_setModeOnOff();
}


void controlPoll(void){


		switch(statusControlFSM){
		case CONTROL_IDLE:

			if(delayRead(&delayTemp))
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

static void controlProcess()
{
	if((temperature > minTemp) && (temperature < maxTemp)) //si estoy dentro del rango
	{
		normalSequence();
		return;
	}
	if (temperature >= maxTemp)
	{
		hotSequence();
		return;
	}
	if (temperature <= minTemp)
	{
		coldSequence();
		return;
	}


	statusControlFSM = CONTROL_ERROR;

}

static void normalSequence()
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

	if(TLC5923_setOutputsOnOff(data))
	{
		return;
	}
	else
	{
		statusControlFSM = CONTROL_ERROR;
	}

}

static void coldSequence()
{
	uint16_t data = 0b0101010110101010;

	if(TLC5923_setOutputsOnOff(data))
	{
		return;
	}
	else
	{
		statusControlFSM = CONTROL_ERROR;

		return;
	}
}

static void hotSequence()
{
	uint16_t dataGreen = 0b1010101001010101;
	uint16_t dataZero = 0b0000000000000000;

	if(delayRead(&delayAlert))
	{
		if( flagAlert == 0)
		{
			if(TLC5923_setOutputsOnOff(dataGreen))
			{
				flagAlert = 1;
			}
			else
			{
				statusControlFSM = CONTROL_ERROR;
			}

		}
		else
		{
			if(TLC5923_setOutputsOnOff(dataZero))
			{
				flagAlert = 0;
			}
			else
			{
				statusControlFSM = CONTROL_ERROR;
			}

		}
	}

}

static void errorSequence()
{
	uint16_t dataBlue = 0b0100010010001000;
	uint16_t dataGreen = 0b0010001000010001;

	if(delayRead(&delayError))
	{
		if( flagError == 0)
		{
			if(TLC5923_setOutputsOnOff(dataBlue))
			{
				flagError = 1;
			}
			else
			{
				statusControlFSM = CONTROL_ERROR;
			}

		}
		else
		{
			if(TLC5923_setOutputsOnOff(dataGreen))
			{
				flagError = 0;
			}
			else
			{

				statusControlFSM = CONTROL_ERROR;
			}


		}
	}

}

void setMaxTemp(float t)
{
	maxTemp = t;
}

void setMinTemp(float t)
{
	minTemp = t;
}

float getMaxTemp(void)
{
	return maxTemp;
}

float getMinTemp(void)
{
	return minTemp;
}

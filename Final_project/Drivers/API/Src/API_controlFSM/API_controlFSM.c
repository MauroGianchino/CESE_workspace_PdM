/*
 * API_controlFSM.c
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */


#include "API_controlFSM.h"




typedef enum{
	IDLE = 0,
	READ_TEMPERATURE,
	PROCESS,
	ERROR
} controlState_t;

static controlState_t statusControlFSM;

static delay_t delay;

static tick_t durationDelay = 1000; //1 segundo de tiempo base entre mediciones de temperatura

float temperature; //variable que guarda la temperatura leida

float maxTemp; //variable que guarda el valor alto del rango de temperatura

float minTemp; //variable que guarda  el valor bajo del rango de temperatura

void controlInit(void){

	statusControlFSM = IDLE;
	delayInit(&delay,durationDelay);
}


void controlPoll(void){


		switch(statusControlFSM){
		case IDLE:
			if(delayRead(&delay))
			{
				statusControlFSM = READ_TEMPERATURE;
			}

			break;
		case READ_TEMPERATURE:
			if(TMP117_readTemperature(&temperature))
			{
				statusControlFSM = PROCESS;
			}
			else
			{
				statusControlFSM = ERROR;
			}

			break;
		case PROCESS:

			break;
		case ERROR:

			break;
		default:
			statusControlFSM = IDLE;
			break;
		}

}

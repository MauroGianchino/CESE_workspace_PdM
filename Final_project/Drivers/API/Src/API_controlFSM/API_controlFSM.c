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

static controlState_t status;

void controlInit(void){

	status = IDLE;
}


void controlPoll(void){


		switch(status){
		case IDLE:

			break;
		case READ_TEMPERATURE:

			break;
		case PROCESS:

			break;
		case ERROR:

			break;
		default:
			status = IDLE;
			break;
		}

}

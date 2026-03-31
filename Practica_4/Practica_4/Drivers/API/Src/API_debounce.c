/*
 * API_debounce.c
 *
 *  Created on: 26 mar 2026
 *      Author: magian
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h" //debo agregar la HAL para usar sus funciones en este módulo
#include "main.h"


#define DELAY_DEBOUNCE 40


typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
} debounceState_t;


static debounceState_t estadoActual = 0;

static bool_t edge;

static delay_t	delayFSM;


void buttonPressed(void)
{
	//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); //enciendo el led (punto 1)
	edge = true; //si el boton fue presionado cambio
}

void buttonReleased(void)
{
	//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); // apago el led (punto 1)
}


bool_t readKey(void){

	bool_t aux = edge;

	if(edge){
		edge = false;
	}

	return aux;
}


void debounceFSM_init(void){

	estadoActual = BUTTON_UP;
	delayInit(&delayFSM, DELAY_DEBOUNCE);

}

void debounceFSM_update(void){
	// Leer la entrada
	uint8_t button_level = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin); // leo el estado del pin del boton

	/*//punto 1
	 * if(button_level){ // si es true el boton NO esta apretado
		buttonReleased();
	}
	else{
		buttonPressed(); //si es false el boton esta apretado
	}*/

	switch (estadoActual) {

		case BUTTON_UP: // estado inicial boton levantado
			// Condicion de cambio;
			if(!button_level){		// si detecto que lo presione
				estadoActual = BUTTON_FALLING;
				delayRead(&delayFSM); //empiezo el timer
			}

		break;
		case BUTTON_FALLING:

			if(delayRead(&delayFSM)){

				if (!button_level){ //el boton sigue presionado
					estadoActual = BUTTON_DOWN; //confirmo que esta presionado
					buttonPressed(); //el boton fue presionado y con esto se cambia la variable para cambiar la frecuencia de parpadeo del led
				}else{
					estadoActual = BUTTON_UP; //fue un rebote y vuelvo al estado de levantado
				}
			}

		break;

		case BUTTON_DOWN: //estado de boton: presionado
			// Condicion de cambio;
			if(button_level){ //si NO esta presionado
				estadoActual = BUTTON_RISING; //indico que esta en rising
				delayRead(&delayFSM); //inicio el delay
			}
		break;

		case BUTTON_RISING:
			if(delayRead(&delayFSM)){

				if (button_level){ //si no esta apretado, es que se levantó efectivamente
					estadoActual = BUTTON_UP;


				}else{ //el boton sigue bajo, entonces sigue presionado
					estadoActual = BUTTON_DOWN;
				}
			}
		break;

		default:
			estadoActual = BUTTON_UP;

	}

}

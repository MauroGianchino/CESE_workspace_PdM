/*
 * API_cmdparser.c
 *
 *  Created on: 6 abr 2026
 *      Author: Mauro
 */

#include "API_uart.h"
#include "API_cmdparser.h"
#include "string.h"
#include "main.h"


typedef enum{
	CMD_IDLE = 0,
	CMD_RECEIVING,
	CMD_PROCESS,
	CMD_EXEC,
	CMD_ERROR
} cmdParserState_t;

static cmdParserState_t status;
static uint8_t ledStatus = 0;
static uint8_t errType = 0; // err_type = 0 implica linea muy larga, = 1 implica comando desconocido, = 3 implica argumentos erroneos.

static uint8_t cmdBuffer[CMD_MAX_LINE]; // arreglo para la recepcion de caracteres
static uint16_t cmdIndex = 0; //indice para moverme en el arreglo

void cmdParserInit(void){

	status = CMD_IDLE;
	uartInit();
}


void cmdPoll(void){

	uint8_t c;

		switch(status){
		case CMD_IDLE:
			if(uartReceiveStringSize(&c,1)){
				uartSendStringSize(&c,1);
			if (c != '\r' && c != '\n'){
				cmdIndex = 0;
				status = CMD_RECEIVING; //cambio estado a receiving
				cmdBuffer[cmdIndex]=c; // asigno lo recibido a la primera posicion del buffer
				cmdIndex++; //incremento el indice
			}}
			break;
		case CMD_RECEIVING:
			if(uartReceiveStringSize(&c,1)){
							uartSendStringSize(&c,1);
			if (c == '\r' || c == '\n'){
				status = CMD_PROCESS; //paso a procesar la linea
				cmdBuffer[cmdIndex]='\0'; //le agrego un /0 para indicar el final de linea
				uartSendString(cmdBuffer);
			}
			else{
				if(cmdIndex < CMD_MAX_LINE - 1){ //chequeo si no se superó el maximo del buffer que es 64
					cmdBuffer[cmdIndex] = c; //asigno el caracter al buffer
					cmdIndex++; //incremento indice
				}
				else{ //si se supero la longitud maxima, error
					status = CMD_ERROR;
					errType = 0;
				}

			}}
			break;
		case CMD_PROCESS:
			cmdProcessLine(); //se ejecuta la funcion que valida la linea
			break;
		case CMD_EXEC:
			cmdExecute(); //se ejecuta la funcion que hace lo qeu se envio en el comando
			break;
		case CMD_ERROR: //se ejecuta al funcion para escribir error en caso que lo hubiese
			cmdError();
			status = CMD_IDLE;
			break;
		default:
			status = CMD_IDLE;
			break;
		}

}



void cmdPrintHelp(void){

	uartSendString((uint8_t*)"AYUDA: lista de comandos \r\n LED ON \r\n LED OFF \r\n LED TOOGLE \r\n STATUS \r\n "); // printeo la linea de comandos

}


static void cmdProcessLine(){

	if (strlen((char*)cmdBuffer) == 0){ //si no tiene caracteres el buffer, vuelvo
		status = CMD_IDLE;
		return;
	}

	else if(cmdBuffer[0] == '#'){ //ignorar linea que empieza con el caracter '#'
		uartSendString((uint8_t*)"Linea ignorada\r\n");
		status = CMD_IDLE;
	}

	else if(strlen((char*)cmdBuffer) >2){ //ignorar linea que empieza con los caracteres '//'
		if(cmdBuffer[0] == '/' && cmdBuffer[1] == '/'){
			uartSendString((uint8_t*)"Linea ignorada\r\n");
			status = CMD_IDLE;
		}
		else{
			status = CMD_EXEC; // si la linea es aceptable, paso al comando EXEC
		}


	}
}


static void cmdExecute(){

	if (strcasecmp((char*)cmdBuffer, "HELP") == 0) { // comparo de manera case-insensitive con el comando HELP
		cmdPrintHelp();
		status = CMD_IDLE;
	}

	else if(strcasecmp((char*)cmdBuffer, "LED ON") == 0){ // comparo de manera case-insensitive
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); //prendo led
		ledStatus = 1;
		status = CMD_IDLE;

	}
	else if(strcasecmp((char*)cmdBuffer, "LED OFF") == 0){ // comparo de manera case-insensitive
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); //apago led
		ledStatus = 0;
		status = CMD_IDLE;

	}
	else if(strcasecmp((char*)cmdBuffer, "LED TOGGLE") == 0){ // comparo de manera case-insensitive
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); //toggleo el led
		if(ledStatus == 1){ //cambio la variable para conocer el estado y usarlo para  el comando STATUS
			ledStatus = 0;
		}
		else{
			ledStatus = 1;
		}
		status = CMD_IDLE;
	}

	else if (strcasecmp((char*)cmdBuffer, "STATUS") == 0) { //comparo de manera case-insensitive

		if(ledStatus == 1){
			uartSendString((uint8_t*)"El estado del led es: ON\r\n");
		}
		else{
			uartSendString((uint8_t*)"El estado del led es: OFF\r\n");
		}
		status = CMD_IDLE;

	}
	else{ //si no es aceptado, es que lo ingresado no es un comando
		errType = 1;
		status = CMD_ERROR;
	}

}


static void cmdError(){

	if (errType== 0){
		uartSendString((uint8_t*)"ERROR: line too long\r\n");
	}
	else if (errType== 1){
		uartSendString((uint8_t*)"ERROR: unknown command\r\n");
	}
	else if (errType== 2){
		uartSendString((uint8_t*)"ERROR: bad arguments\r\n");
	}
	else{

	}

}

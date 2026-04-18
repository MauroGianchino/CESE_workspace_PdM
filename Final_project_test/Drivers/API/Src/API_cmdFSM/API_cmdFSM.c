/*
 * API_cmdFSM.c
 *
 *  Created on: 17 abr 2026
 *      Author: Mauro
 */



#include "API_cmdFSM.h"

float temp=0;

float minRange=0;

float maxRange=0;
/**
 * @brief Funcion de procesamiento de linea
 */
static void cmdProcessLine(void);

/**
 * @brief Funcion de ejecución de comando
 */
static void cmdExecute(void);

/**
 * @brief Funcion de error
 */
static void cmdError(void);

typedef enum{
	CMD_IDLE = 0,
	CMD_RECEIVING,
	CMD_PROCESS,
	CMD_EXEC,
	CMD_ERROR
} cmdParserState_t;

typedef enum{
	ERROR_LINE_LONG = 0,
	ERROR_UNKNOwN_COMMAND,
	ERROR_BAD_ARGUMENTS
} error_t;

static cmdParserState_t status;

static error_t errType; // err_type = 0 implica linea muy larga, = 1 implica comando desconocido, = 3 implica argumentos erroneos.

static uint8_t cmdBuffer[CMD_MAX_LINE]; // arreglo para la recepcion de caracteres
static uint16_t cmdIndex = 0; //indice para moverme en el arreglo

void cmdInit(void){

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
					errType = ERROR_LINE_LONG;
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

	uartSendString((uint8_t*)"AYUDA: lista de comandos \r\n GET TEMP \r\n GET RANGE \r\n GET ALERT \r\n SET TL x \r\n SET TH x \r\n HELP\r\n"); // printeo la linea de comandos

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

	else if(strcasecmp((char*)cmdBuffer, "GET TEMP") == 0){ // comparo de manera case-insensitive
		temp = getTemp();
		char msg[32]; // Espacio suficiente para el texto y el número
		snprintf(msg, sizeof(msg), "Temperature: %.2f °C\r\n", temp);
		uartSendString((uint8_t*)msg);
		status = CMD_IDLE;

	}
	else if(strcasecmp((char*)cmdBuffer, "GET RANGE") == 0){ // comparo de manera case-insensitive
		minRange = getMinTemp();
		maxRange = getMaxTemp();
		char msg[64];
		snprintf(msg, sizeof(msg), "Range: Min %.2f °C - Max %.2f °C\r\n", minRange, maxRange);
		uartSendString((uint8_t*)msg);
		status = CMD_IDLE;

	}
	else if(strcasecmp((char*)cmdBuffer, "GET ALERT") == 0)
	{ // comparo de manera case-insensitive
		status = CMD_IDLE;
	}
	else if(strncasecmp((char*)cmdBuffer, "SET TL ",7) == 0)
		{ // Detecto hasta la posición 7 porque luego se encuentra el numero

		float ntemp;
		if(sscanf((char*)cmdBuffer + 7, "%f", &ntemp) == 1)
		{
			if(ntemp < getMaxTemp())
			{
				setMinTemp(ntemp);
			}
			else
			{
				uartSendString((uint8_t*)"Error: Valor de temperatura TL no puede ser mayor o igual a TH\r\n");
			}

		}
		else
		{
			uartSendString((uint8_t*)"Error: Valor de temperatura invalido\r\n");
		}
		status = CMD_IDLE;
	}
	else if(strncasecmp((char*)cmdBuffer, "SET TH ",7) == 0)
		{ // Detecto hasta la posición 7 porque luego se encuentra el numero

		float ntemp;
		if(sscanf((char*)cmdBuffer + 7, "%f", &ntemp) == 1)
		{
			if(ntemp > getMinTemp())
			{
				setMaxTemp(ntemp);
			}
			else
			{
				uartSendString((uint8_t*)"Error: Valor de temperatura TH no puede ser menor o igual a TL\r\n");
			}
		}

		else
		{
			uartSendString((uint8_t*)"Error: Valor de temperatura invalido\r\n");
		}
		status = CMD_IDLE;
	}
	else{ //si no es aceptado, es que lo ingresado no es un comando
		errType = ERROR_UNKNOwN_COMMAND;
		status = CMD_ERROR;
	}

}


static void cmdError(){

	if (errType== ERROR_LINE_LONG){
		uartSendString((uint8_t*)"ERROR: line too long\r\n");
	}
	else if (errType== ERROR_UNKNOwN_COMMAND){
		uartSendString((uint8_t*)"ERROR: unknown command\r\n");
	}
	else if (errType== ERROR_BAD_ARGUMENTS){
		uartSendString((uint8_t*)"ERROR: bad arguments\r\n");
	}
	else{

	}

}

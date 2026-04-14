/*
 * API_cmdparser.h
 *
 *  Created on: 6 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_API_CMDPARSER_H_
#define API_INC_API_CMDPARSER_H_

#define CMD_MAX_LINE 64 //incluye '/0'
#define CMD_MAX_TOKENS 3 //COMANDO + maximo 2 argumentos

typedef enum {
	CMD_OK = 0,
	CMD_ERR_OVERFLOW,
	CMD_ERR_SYNTAX,
	CMD_ERR_UNKNOWN,
	CMD_ERR_ARG
}cmd_status_t;


/**
 * @brief Inicializa el modulo parser de comandos
 */
void cmdParserInit(void);

/**
 * @brief Maquina de estados del parser. Debe ser llamada periodiamente desde el bucle.
 * Procesa hasta 16 bytes por invocacion (no bloqueante)
 */

void cmdPoll(void);

/**
 * @brief Imprime por UART la lista de comandos disponibles
 */

void cmdPrintHelp(void);


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




#endif /* API_INC_API_CMDPARSER_H_ */

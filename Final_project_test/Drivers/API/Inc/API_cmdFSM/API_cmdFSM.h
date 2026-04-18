/*
 * API_cmdFSM.h
 *
 *  Created on: 17 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_API_CMDFSM_API_CMDFSM_H_
#define API_INC_API_CMDFSM_API_CMDFSM_H_

#define CMD_MAX_LINE 64 //incluye '/0'
#define CMD_MAX_TOKENS 3 //COMANDO + maximo 2 argumentos

#include "API_uart.h"
#include "string.h"
#include "main.h"
#include "API_controlFSM.h"
#include <stdint.h>
#include <stdbool.h>


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
void cmdInit(void);

/**
 * @brief Maquina de estados del parser. Debe ser llamada periodiamente desde el bucle.
 * Procesa hasta 16 bytes por invocacion (no bloqueante)
 */

void cmdPoll(void);

/**
 * @brief Imprime por UART la lista de comandos disponibles
 */

void cmdPrintHelp(void);



#endif /* API_INC_API_CMDFSM_API_CMDFSM_H_ */

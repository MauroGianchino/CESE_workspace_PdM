/*
 * API_uart.h
 *
 *  Created on: 9 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Inicializa el periférico USART2 con una configuración predefinida (115200, 8N1).
 * Tras una inicialización exitosa, envía por UART los parámetros de configuración.
 * @param ninguno
 * @return bool true si la inicialización fue exitosa, false en caso de error.
 */
bool uartInit(void);

/**
 * @brief Envía una cadena de caracteres por UART.
 * @param pstring Puntero al array de caracteres (string) a enviar.
 */
void uartSendString(uint8_t * pstring);

/**
 * @brief Envía una cantidad específica de bytes por UART seguidos de un salto de línea.
 * @param pstring Puntero a los datos que se desean enviar.
 * @param size    Cantidad de bytes a transmitir.
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/**
 * @brief Recibe una cantidad específica de bytes por UART y los almacena en un buffer.
 * @param pstring Puntero al buffer donde se guardarán los datos recibidos.
 * @param size    Cantidad de bytes que se espera recibir.
 */
bool uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */

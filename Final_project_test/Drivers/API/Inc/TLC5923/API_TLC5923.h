/*
 * API_TLC5923.h
 *
 *  Created on: 9 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_API_TLC5923_H_
#define API_INC_API_TLC5923_H_

#include "TLC5923_port.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

/**
 * @brief Inicializa el driver de LEDs TLC5923 con configuración por defecto.
 * * Esta función realiza la secuencia de arranque del dispositivo:
 * 1. Configura el brillo de todos los canales al máximo (Dot Correction al 100%).
 * 2. Habilita las salidas globales del integrado.
 * 3. Cambia el modo de operación a On/Off para permitir el control de los LEDs.
 * * @note La función asume que el periférico de comunicación (SPI) ya ha sido
 * inicializado previamente en la capa de puerto.
 * * @return true  Si la configuración inicial se envió correctamente por el bus.
 * @return false Si falló el envío de la trama de Dot Correction (DC).
 */
bool TLC5923_init(void);

/**
 * @brief Desactiva todas las salidas del driver TLC5923.
 * * Pone los canales de salida en estado de alta impedancia (OFF),
 * apagando todos los LEDs conectados de forma global.
 */
void TLC5923_disableOutputs(void);

/**
 * @brief Activa las salidas del driver TLC5923.
 * * Habilita la operación de los canales de salida según la configuración
 * previa de datos.
 */
void TLC5923_enableOutputs(void);

/**
 * @brief Configura el dispositivo en modo Dot Correction (DC).
 * * Ajusta el pin de control de modo para permitir la escritura de los
 * registros de control de corriente (Dot Correction) de cada canal.
 */
void TLC5923_setModeDC(void);

/**
 * @brief Configura el dispositivo en modo On/Off.
 * * Ajusta el pin de control de modo para permitir la escritura de los
 * registros de estado de encendido/apagado de los canales.
 */
void TLC5923_setModeOnOff(void);

/**
 * @brief Define el estado de encendido/apagado para los 16 canales.
 * * @param[in] outputs Máscara de 16 bits donde cada bit representa un canal (1: ON, 0: OFF).
 * @return true Si el envío de datos por la capa de puerto fue exitoso.
 * @return false Si hubo un error en la transferencia.
 */
bool TLC5923_setOutputsOnOff(uint16_t outputs);

/**
 * @brief Configura la corriente (Dot Correction) para las salidas.
 * * Permite ajustar la intensidad de brillo individual de los canales
 * mediante la escritura en los registros DC.
 * * @param[in] arreglo de 7 datos tipo u16.
 * @return true Si los datos se enviaron correctamente.
 * @return false Si falló la comunicación.
 */
bool TLC5923_setOutputsDC(uint16_t* outputs);

#endif /* API_INC_API_TLC5923_H_ */

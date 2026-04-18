/*
 * TLC5923_port.h
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_TLC5923_TLC5923_PORT_H_
#define API_INC_TLC5923_TLC5923_PORT_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Envía un flujo de bytes al driver TLC5923 mediante el protocolo físico (SPI).
 * * Esta es la función de abstracción de hardware que gestiona el envío de datos
 * crudos a través del periférico configurado en el STM32.
 * * @param[in] pData Puntero al array de bytes que contiene la trama de datos a transmitir.
 * @return true Si la transmisión SPI se completó sin errores.
 * @return false Si la capa de hardware (HAL) reportó un error de timeout o bus.
 */
bool writeData(uint8_t*);

#endif /* API_INC_TLC5923_TLC5923_PORT_H_ */

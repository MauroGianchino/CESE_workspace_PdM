/*
 * API_controlFSM.h
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_API_CONTROLFSM_API_CONTROLFSM_H_
#define API_INC_API_CONTROLFSM_API_CONTROLFSM_H_

#include <API_comms.h>
#include "stm32f4xx_hal.h"
#include "API_delay.h"
#include <stdbool.h>
#include <stdint.h>
#include "API_TMP117.h"
#include "API_TLC5923.h"
#include "API_GPIO.h"

/**
 * @brief Inicializa la Máquina de Estados Finitos (FSM) de control.
 * * Configura los valores iniciales de los umbrales de temperatura y prepara
 * los periféricos asociados para el ciclo de control.
 */
void controlInit(void);

/**
 * @brief Ejecuta una iteración de la lógica de control (polling).
 * * Lee la temperatura actual del sensor TMP117, actualiza el estado de la FSM
 * y ajusta la iluminación de los LEDs mediante el TLC5923 según los umbrales
 * configurados. Esta función debe ser llamada periódicamente en el loop principal.
 */
void controlPoll(void);

/**
 * @brief Configura el umbral máximo de temperatura.
 * * @param[in] temp Valor float que define el límite superior para la lógica de control.
 */
void setMaxTemp(float);

/**
 * @brief Configura el umbral mínimo de temperatura.
 * * @param[in] temp Valor float que define el límite inferior para la lógica de control.
 */
void setMinTemp(float);

/**
 * @brief Obtiene el valor configurado del umbral máximo.
 * * @return float Valor actual de la temperatura máxima de consigna.
 */
float getMaxTemp(void);

/**
 * @brief Obtiene el valor configurado del umbral mínimo.
 * * @return float Valor actual de la temperatura mínima de consigna.
 */
float getMinTemp(void);

/**
 * @brief Devuelve la última temperatura leída por el sistema.
 * * Proporciona el valor capturado durante la última ejecución de controlPoll.
 * * @return float Temperatura actual en grados Celsius.
 */
float getTemp(void);

#endif /* API_INC_API_CONTROLFSM_API_CONTROLFSM_H_ */

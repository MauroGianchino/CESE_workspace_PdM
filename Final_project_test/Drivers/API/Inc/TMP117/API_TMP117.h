/*
 * TMP117.h
 *
 *  Created on: 9 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_API_TMP117_H_
#define API_INC_API_TMP117_H_

#include "TMP117_port.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "API_GPIO.h"

/**
 * @brief Lee el identificador único del sensor TMP117.
 * * Esta función consulta el registro de identificación del dispositivo para verificar
 * que la comunicación I2C sea correcta y que el modelo de sensor sea el esperado.
 * * @param[out] id Puntero a una variable de 16 bits donde se almacenará el ID leído.
 * @return true Si el ID se leyó correctamente.
 * @return false Si hubo un error en la comunicación I2C.
 */
bool TMP117_readID(uint16_t*);

/**
 * @brief Obtiene la temperatura actual medida por el sensor TMP117.
 * * Lee el registro de temperatura y realiza la conversión interna a grados Celsius
 * según la resolución del sensor (7.8125 mC por LSB).
 * * @param[out] temp Puntero a un float donde se guardará el valor de temperatura en °C.
 * @return true Si la lectura y conversión fueron exitosas.
 * @return false Si falló la comunicación con el sensor.
 */
bool TMP117_readTemperature(float *);

#endif /* API_INC_API_TMP117_H_ */

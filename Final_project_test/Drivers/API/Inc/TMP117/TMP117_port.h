/*
 * TMP117_port.h
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_TMP117_PORT_H_
#define API_INC_TMP117_PORT_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

bool readRegister(uint16_t address, uint8_t regAddress, uint8_t *pData);
bool writeRegister(uint16_t address, uint8_t regAddress, uint16_t data);

#endif /* API_INC_TMP117_PORT_H_ */

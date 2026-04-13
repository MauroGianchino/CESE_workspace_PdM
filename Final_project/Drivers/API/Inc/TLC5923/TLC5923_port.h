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

bool writeData(uint8_t*);

#endif /* API_INC_TLC5923_TLC5923_PORT_H_ */

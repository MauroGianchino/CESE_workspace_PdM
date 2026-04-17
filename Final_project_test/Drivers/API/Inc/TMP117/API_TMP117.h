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
#include "main.h"

bool TMP117_readID(uint16_t*);
bool TMP117_readTemperature(float *);

#endif /* API_INC_API_TMP117_H_ */

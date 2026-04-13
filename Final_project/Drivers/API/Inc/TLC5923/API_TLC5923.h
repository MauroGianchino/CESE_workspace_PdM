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
#include "API_GPIO.h"

void setBlank(void);
void resetBlank(void);
void setModeDC(void);
void setModeOnOff(void);
bool setOutputs(uint16_t outputs);

#endif /* API_INC_API_TLC5923_H_ */

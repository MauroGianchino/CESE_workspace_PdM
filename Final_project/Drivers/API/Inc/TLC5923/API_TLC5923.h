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

void TLC5923_disableOutputs(void);
void TLC5923_enableOutputs(void);
void TLC5923_setModeDC(void);
void TLC5923_setModeOnOff(void);
bool TLC5923_setOutputs(uint16_t outputs);

#endif /* API_INC_API_TLC5923_H_ */

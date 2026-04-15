/*
 * API_controlFSM.h
 *
 *  Created on: 12 abr 2026
 *      Author: Mauro
 */

#ifndef API_INC_API_CONTROLFSM_API_CONTROLFSM_H_
#define API_INC_API_CONTROLFSM_API_CONTROLFSM_H_

#include "stm32f4xx_hal.h"
#include "API_delay.h"
#include <stdbool.h>
#include <stdint.h>
#include "API_TMP117.h"

void controlInit(void);
void controlPoll(void);

#endif /* API_INC_API_CONTROLFSM_API_CONTROLFSM_H_ */

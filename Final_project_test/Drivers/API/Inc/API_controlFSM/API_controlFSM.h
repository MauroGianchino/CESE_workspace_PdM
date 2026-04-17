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
#include "API_TLC5923.h"
#include "main.h"

void controlInit(void);
void controlPoll(void);
static void controlProcess(void);
static void normalSequence(void);
static void coldSequence(void);
static void errorSequence(void);
static void hotSequence(void);
void setMaxTemp(float);
void setMinTemp(float);
float getMaxTemp(void);
float getMinTemp(void);

#endif /* API_INC_API_CONTROLFSM_API_CONTROLFSM_H_ */

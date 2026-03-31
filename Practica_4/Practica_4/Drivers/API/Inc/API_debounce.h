/*
 * API_debounce.c
 *
 *  Created on: 26 mar 2026
 *      Author: magian
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_delay.h"
/*
 * @brief initialize debounce State Machine
 * @param no params
*/
void debounceFSM_init(void);		// debe cargar el estado inicial

/*
 * @brief update State Machine
 * @param no params
*/

void debounceFSM_update(void);		// debe leer las entradas, resolver la lógica de
								// transición de estados y actualizar las salidas

/*
 * @brief gets if button was pressed. True if it was pressed (falling edge), false if not.
 * @param no params
*/
bool_t readKey(void);

#endif  API_INC_API_DEBOUNCE_H_

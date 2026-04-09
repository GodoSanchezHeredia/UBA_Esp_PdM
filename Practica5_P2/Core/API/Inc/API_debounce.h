/*
 * API_debounce.h
 *
 *  Created on: Apr 9, 2026
 *      Author: USER
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_


#include "API_delay.h"

// Init FSM
void debounceFSM_init(void);

// update FSM
void debounceFSM_update(void);

/*
 * devuelve TRUE  1 sola vez cuando se detecta un flanco descendente
 * Luego se resetea ().
 */
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */

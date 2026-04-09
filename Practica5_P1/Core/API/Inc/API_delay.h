/*
 * API_delay.h
 *
 *  Created on: Mar 25, 2026
 *      Author: USER
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t tick_t; 	// Qué biblioteca se debe incluir para que esto compile?  -> #include <stdint.h>
typedef bool bool_t;		// Qué biblioteca se debe incluir para que esto compile?  -> #include <stdbool.h>

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/**
 * @brief Inicializa la  estructura del retardo no bloqueante
 *
 * @param delay Puntero
 * @param duration tiempo del retardo
 */
void delayInit( delay_t * delay, tick_t duration );

/**
 * @brief Verifica el estado del delay
 *
 * @param delay Puntero
 * @return retorna TRUE si se cumplio el tiempo, FALSE si todavia
 */
bool_t delayRead( delay_t * delay );

/**
 * @brief Actualiza la duracion del retardo
 *
 * @param delay Puntero
 * @param duration la duiracion del nuevo retardo
 */
void delayWrite( delay_t * delay, tick_t duration );

/**
 * @brief debe devolver una copia del valor del campo running
 *
 * @param delay Puntero
 * @return debe devolver un booleano
 */
bool_t delayIsRunning(delay_t * delay);

#endif /* API_INC_API_DELAY_H_ */

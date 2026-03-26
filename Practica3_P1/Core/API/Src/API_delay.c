/*
 * API_delay.c
 *
 *  Created on: Mar 25, 2026
 *      Author: Godo Sanchez
 */

#include "API_delay.h"
#include "main.h"




void delayInit( delay_t * delay, tick_t duration ){
	delay->running = false;
	delay->duration = duration;
	delay->startTime =0;
}

bool_t delayRead( delay_t * delay ){

	switch (delay->running) {
		case true:
			if (HAL_GetTick()-delay->startTime>=delay->duration) {
				delay->running = false;
				return true;
			}
			else{return false;}

			break;
		case false:
			delay->startTime =  HAL_GetTick();
			delay->running = true;
			return false;

			break;
		default:
			//Error_Handler();
			break;
	}
	return true;
}

void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration = duration;
}

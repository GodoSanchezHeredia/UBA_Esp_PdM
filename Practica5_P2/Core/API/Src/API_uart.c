/*
 * API_uart.c
 *
 *  Created on: Apr 9, 2026
 *      Author: USER
 */

#include "API_uart.h"
#include "usart.h"
#include "string.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

#define uartTimeout 100

static bool isValidSize(uint16_t size){
	bool data =false;
	if ((size > 0 && size <= 256)) {
		data =true;
	}else {
		data =false;
	}
    return data;
}


bool uartInit(){

    if(HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY){
        return HAL_ERROR;
    }
    uint8_t msg[] = "PdM:UART Init OK\n\r";

    if(HAL_UART_Transmit(&huart2, msg, sizeof(msg)-1, uartTimeout) != HAL_OK){
        return HAL_OK;
    }

    return HAL_OK;
}

void uartSendString(uint8_t * pstring){

	if (pstring == NULL  ) {
		Error_Handler();
	}

    uint16_t size = strlen((char*)pstring);

    if(!isValidSize(size)){
        return;
    }

    if(HAL_UART_Transmit(&huart2, pstring, size, uartTimeout) != HAL_OK){
        return;
    }
}
void uartSendStringSize(uint8_t * pstring, uint16_t size){

	if (pstring == NULL  ) {
		Error_Handler();
	}

    if(!isValidSize(size)){
        return ;
    }

    if(HAL_UART_Transmit(&huart2, pstring, size, uartTimeout) != HAL_OK){
        return;
    }
}
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	if (pstring == NULL  ) {
		Error_Handler();
	}

    if(!isValidSize(size)){
        return;
    }

    if(HAL_UART_Receive(&huart2, pstring, size, uartTimeout) != HAL_OK){
        return;
    }
}

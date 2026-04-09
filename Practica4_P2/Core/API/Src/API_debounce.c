/*
 * API_debounce.c
 *
 *  Created on: Apr 9, 2026
 *      Author: USER
 */
#include "API_debounce.h"
#include "stm32f4xx_hal.h"

#define DelayAntiRebote 40
#define DelayInicial 0
typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING,
} debounceState_t;


static debounceState_t State;
static delay_t Delay1;
static bool_t keyPressed = false;

static void errorTask();

void debounceFSM_init(){
	State = BUTTON_UP;
	delayInit(&Delay1, DelayInicial);

}
void debounceFSM_update(){

	GPIO_PinState  Button =  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

	switch (State) {
		case BUTTON_UP:
			if (Button == GPIO_PIN_RESET) {
				State = BUTTON_FALLING;
				delayWrite(&Delay1, DelayAntiRebote);
				delayRead(&Delay1);
			}
			break;
		case BUTTON_FALLING:
			if(delayRead(&Delay1)){
				if(Button == GPIO_PIN_RESET){
					State = BUTTON_DOWN;
					//buttonPressed();
					keyPressed = true;
				} else {
					State = BUTTON_UP;
					}
				}
			break;
		case BUTTON_DOWN:
            if(Button == GPIO_PIN_SET){
                State = BUTTON_RAISING;
                delayWrite(&Delay1, DelayAntiRebote);
                delayRead(&Delay1);
            }
			break;
		case BUTTON_RAISING:
            if(delayRead(&Delay1)){
                if(Button == GPIO_PIN_SET){
                    State = BUTTON_UP;
                    //buttonReleased();
                } else {
                    State = BUTTON_DOWN;
                }
            }
			break;
		default:
			errorTask();
			break;
	}
}


static void errorTask(){
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	HAL_Delay(200);
}

bool_t readKey(void){
    if(keyPressed){
        keyPressed = false; // reset automático
        return true;
    }
    return false;
}

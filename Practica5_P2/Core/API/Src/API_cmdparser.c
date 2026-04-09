/*
 * API_cmdparser.c
 *
 *  Created on: Apr 9, 2026
 *      Author: USER
 */
#include "API_cmdparser.h"
#include "API_delay.h"
#include "API_uart.h"
#include "gpio.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CMD_IDLE,
    CMD_RECEIVING,
    CMD_PROCESS,
    CMD_EXEC,
    CMD_ERROR
} cmdState_t;

#define TimeToggle  500


// Buffer para almacenar la trama UART. Se define CMD_MAX_LINE
// para evitar que un comando muy largo pise memoria crítica.
static uint8_t lineBuffer[CMD_MAX_LINE];
static uint8_t idx = 0; // indice


static uint8_t *tokens[CMD_MAX_TOKENS];
static uint8_t tokenCount = 0;
static delay_t DelayToggle;
static bool_t ledToggleEnabled = false;

static cmdState_t state;
static cmd_status_t cmdStatus;

static void cmdProcessLine(void);
static void cmdExecute(void);
static void cmdErrorPrint(void);
static void toUpperStr(uint8_t *str);
static void cmdUpdateLedToggle(void);

void cmdParserInit(void){
    state = CMD_IDLE;
    idx = 0;
    delayInit(&DelayToggle, TimeToggle); //EL LED DE TOGGLE
    ledToggleEnabled = false;
}

void cmdPoll(void){

    uint8_t c = 0;

    cmdUpdateLedToggle();// Maneja el togle  si esta activo

    uartReceiveStringSize(&c, 1);

    if(c != 0 && c != '\r' && c != '\n'){
        uartSendStringSize(&c, 1); //Si el carácter es válido, lo devolvemos para ver qué escribimos
    }

    switch(state){

        case CMD_IDLE:
            if(c != 0 && c != '\r' && c != '\n'){
                idx = 0;
                lineBuffer[idx++] = c;
                state = CMD_RECEIVING;
            }
        break;

        case CMD_RECEIVING:
            if(c == 0){
                break;
            }

            if(c == '\r' || c == '\n'){
                lineBuffer[idx] = '\0';

                if(lineBuffer[0] == '#' ||
                  (lineBuffer[0] == '/' && lineBuffer[1] == '/')){
                    idx = 0;
                    state = CMD_IDLE;
                    break;
                }

                state = CMD_PROCESS;
            } else {
                if(idx >= CMD_MAX_LINE - 1){
                    cmdStatus = CMD_ERR_OVERFLOW;
                    state = CMD_ERROR;
                } else {
                    lineBuffer[idx++] = c;
                }
            }
        break;

        case CMD_PROCESS:
            cmdProcessLine();

            if(cmdStatus == CMD_OK){
                state = CMD_EXEC;
            } else {
                state = CMD_ERROR;
            }
        break;

        case CMD_EXEC:
            cmdExecute();
            idx = 0;
            if(cmdStatus == CMD_OK){
                state = CMD_IDLE;
            } else {
                state = CMD_ERROR;
            }
        break;

        case CMD_ERROR:
            cmdErrorPrint();
            idx = 0;
            state = CMD_IDLE;
        break;
    }
}

static void cmdExecute(void){

	// enviamos los comandos
    if(strcmp((char*)tokens[0], "HELP") == 0){
        cmdPrintHelp();
        return;
    }
    // indicamos el estado del led
    if(strcmp((char*)tokens[0], "STATUS") == 0){
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET){
            uartSendString((uint8_t*)"LED is ON\r\n");
        } else {
            uartSendString((uint8_t*)"LED is OFF\r\n");
        }
        return;
    }
    // comando led si solo manda eso le mandamos error de argumento
    if(strcmp((char*)tokens[0], "LED") == 0){

        if(tokenCount < 2){
            cmdStatus = CMD_ERR_ARG;
            return;
        }
         // lo q que venga despuyes lo parseamos
        toUpperStr(tokens[1]);
        //predner led
        if(strcmp((char*)tokens[1], "ON") == 0){
            ledToggleEnabled = false;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            uartSendString((uint8_t*)"OK\r\n");
            return;
        }
        // apagar led
        if(strcmp((char*)tokens[1], "OFF") == 0){
            ledToggleEnabled = false;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            uartSendString((uint8_t*)"OK\r\n");
            return;
        }
        // iniciamos el toggle
        if(strcmp((char*)tokens[1], "TOGGLE") == 0){
            ledToggleEnabled = !ledToggleEnabled;
            uartSendString((uint8_t*)"OK\r\n");
            return;
        }

        cmdStatus = CMD_ERR_ARG;
        return;
    }

    cmdStatus = CMD_ERR_UNKNOW;
}

static void cmdProcessLine(void){

    char *token = NULL;

    tokenCount = 0;
    // Si la linea arranca con # o // no lo hacemos caso
    if(lineBuffer[0] == '#' ||
      (lineBuffer[0] == '/' && lineBuffer[1] == '/')){
        cmdStatus = CMD_ERR_UNKNOW;
        return;
    }
    // dividmos las  palabras usando espacios  como limitador o fin
    token = strtok((char*)lineBuffer, " \t");

    while(token != NULL && tokenCount < CMD_MAX_TOKENS){
        tokens[tokenCount++] = (uint8_t*)token;
        token = strtok(NULL, " \t");
    }

    if(tokenCount == 0){
        cmdStatus = CMD_ERR_SYNTAX;
        return;
    }
    //parseamos el primer comando
    toUpperStr(tokens[0]);

    cmdStatus = CMD_OK;
}

static void cmdErrorPrint(void){

    switch(cmdStatus){
    	// cuando el com,ando es muy largo
        case CMD_ERR_OVERFLOW:
            uartSendString((uint8_t*)"ERROR: line too long\r\n");
        break;

        case CMD_ERR_UNKNOW:
            uartSendString((uint8_t*)"ERROR: unknown command\r\n");
        break;

        case CMD_ERR_ARG:
            uartSendString((uint8_t*)"ERROR: bad arguments\r\n");
        break;
        case CMD_ERR_SYNTAX:
            uartSendString((uint8_t*)"ERROR: bad syntax\r\n");

        default:
            uartSendString((uint8_t*)"ERROR\r\n");
        break;
    }
}

static void toUpperStr(uint8_t *str){
    while(*str){
        *str = (uint8_t)toupper((int)*str); // para convertir a mayusculas
        str++;
    }
}

static void cmdUpdateLedToggle(void){
    if(ledToggleEnabled && delayRead(&DelayToggle)){
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
}

void cmdPrintHelp(void){
    uartSendString((uint8_t*)
        "Commands:\r\n"
        "HELP\r\n"
        "LED ON\r\n"
        "LED OFF\r\n"
        "LED TOGGLE\r\n"
        "STATUS\r\n");
}

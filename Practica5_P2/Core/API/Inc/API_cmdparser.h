/*
 * API_cmdparser.h
 *
 *  Created on: Apr 9, 2026
 *      Author: USER
 */

#ifndef API_INC_API_CMDPARSER_H_
#define API_INC_API_CMDPARSER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define CMD_MAX_LINE 64 //INCLUYE '\0'
#define CMD_MAX_TOKENS 3 // COMANDO + MAXIMO 2 ARGUMENTOS

typedef enum {
	CMD_OK =0,
	CMD_ERR_OVERFLOW,
	CMD_ERR_SYNTAX,
	CMD_ERR_UNKNOW,
	CMD_ERR_ARG
}cmd_status_t;

// inicializa el modulo parser de comandos
void cmdParserInit(void);

//maquina de estados del parser debe ser llamda periodicamente en el bucle , procesa 16bytes por invocacion no bloqueante
void cmdPoll(void);

//imprime por uart una lista de comandos disponibles
void cmdPrintHelp(void);


#endif /* API_INC_API_CMDPARSER_H_ */

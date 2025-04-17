/*
 * API_uart.h
 *
 *  Created on: Apr 3, 2025
 *      Author: Mariano Deville
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include "main.h"
#include "compatibility.h"

/**
 * Macros
 */
/* Comandos ASCII ----------------------------------------------------------*/
#define CLEAR_SCREEN_AND_HOME	"\e[2J\e[H"
#define CRLF					"\r\n"

/* Definiciones de tamaños y velocidad -------------------------------------*/
#define MAX_TX_BUFFER_UART		128
#define RX_BUFFER_SIZE_UART		20
#define BAUDE_RATE_UART			115200

/**
 * Estructura con la información del puerto.
 */
typedef struct {

	UART_HandleTypeDef * puerto;
	bool_t mensaje_recibido;
	uint8_t rx_buff[RX_BUFFER_SIZE_UART];
}puerto_UART;

/**
 * Prototipo de funciones públicas.
 */
bool_t UARTtInit(puerto_UART * data_port, UART_HandleTypeDef * huart);
Estado_TX_RX UARTSendString(puerto_UART * data_port, const uint8_t * pstring);
Estado_TX_RX UARTSendStringSize(puerto_UART * data_port, const uint8_t * pstring, uint16_t size);
void UARTReceiveStringSize(puerto_UART * data_port, uint16_t size);
bool_t UARTIsNewMessage(puerto_UART * data_port);
bool_t PutConfiguration(puerto_UART * data_port);

#endif /* API_INC_API_UART_H_ */

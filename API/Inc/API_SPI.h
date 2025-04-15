/*
 * API_SPI.h
 *
 *  Created on: Apr 15, 2025
 *      Author: Mariano Deville
 */

#ifndef INC_API_SPI_H_
#define INC_API_SPI_H_


#include "main.h"
#include "compatibility.h"


#define TIME_OUT_SPI	240
#define _1_BYTE			0x0001
#define _2_BYTES		0x0002

/* Definiciones de tamaños y velocidad -------------------------------------*/
#define MAX_TX_BUFFER_SPI			128
#define RX_BUFFER_SIZE_SPI			20

/**
 * Estructura con la información del puerto.
 */
typedef struct {

	SPI_HandleTypeDef * puerto;
	bool_t mensaje_recibido;
	uint8_t rx_buff[RX_BUFFER_SIZE_SPI];
}puerto_SPI;


/**
 * Prototipo de funciones públicas.
 */
bool_t SPIInit(puerto_SPI * data_port, SPI_HandleTypeDef * hspi);
Estado_TX_RX SPISend(puerto_SPI * data_port, const uint8_t * pstring,  uint16_t size);
void SPIReceiveStringSize(puerto_SPI * data_port, uint16_t size);
//bool_t isNewMessage(puerto_SPI * data_port);

#endif /* INC_API_SPI_H_ */

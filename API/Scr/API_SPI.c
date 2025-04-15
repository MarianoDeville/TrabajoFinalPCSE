/*
 * API_SPI.c
 *
 *  Created on: Apr 15, 2025
 *      Author: Mariano Deville
 */
#include "API_SPI.h"
#include "string.h"

/**
  * @brief  Inicialización del puerto serie.
  * @param  Puntero a la estructura que contiene las variabes del puerto seleccionado.
  * @retval Devuelvo verdadero si la inicialización se realizo sin problemas.
  */
bool_t SPIInit(puerto_SPI * data_port, SPI_HandleTypeDef * hspi) {

	data_port->mensaje_recibido = false;
	data_port->puerto = hspi;
	data_port->puerto->Instance = SPI3;
	data_port->puerto->Init.Mode = SPI_MODE_MASTER;
	data_port->puerto->Init.Direction = SPI_DIRECTION_2LINES;
	data_port->puerto->Init.DataSize = SPI_DATASIZE_8BIT;
	data_port->puerto->Init.CLKPolarity = SPI_POLARITY_LOW;
	data_port->puerto->Init.CLKPhase = SPI_PHASE_1EDGE;
	data_port->puerto->Init.NSS = SPI_NSS_SOFT;
	data_port->puerto->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	data_port->puerto->Init.FirstBit = SPI_FIRSTBIT_MSB;
	data_port->puerto->Init.TIMode = SPI_TIMODE_DISABLE;
	data_port->puerto->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	data_port->puerto->Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(hspi) != HAL_OK)
	    return false;
    return true;
}

/**
  * @brief  Envío por el puerto una cadena de caracteres.
  * @param  Puntero a la estructura que contiene las variabes del puerto.
  * @param  Puntero a la cadena que se desea enviar.
  * @param  Tamaño de la cadena a enviar.
  * @retval Devuelvo la información del resultado de la transmisión.
  */
Estado_TX_RX SPISend(puerto_SPI * data_port, const uint8_t * pstring, uint16_t size) {

	HAL_SPI_Transmit(data_port->puerto, pstring, _1_BYTE, size);
	return 0;
}


/**
  * @brief  Recibo un mensaje entrante.
  * @param  Puntero a la estructura que contiene las variabes del puerto.
  * @param  Puntero a la cadena que se usa como buffer de entrada.
  * @param  Tamaño de la cadena que se espera entre.
  * @retval None.
  */
void SPIReceiveStringSize(puerto_SPI * data_port, uint16_t size) {

	HAL_SPI_Receive_IT(data_port->puerto, data_port->rx_buff, size);
	data_port->mensaje_recibido = true;
	return;
}






/**
 *******************************************************************************
 * @file    DriverMRF24J40.X/drivers/src/drv_mrf24j40port.c
 * @author  Lcdo. Mariano Ariel Deville
 * @brief   Implementación driver módulo MRF24J40MA
 *******************************************************************************
 * @attention Este archivo asegura la portabilidad del driver (drv_mrf24j40.c)
 *
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "API_MRF24J40_port.h"
#include "main.h"

extern SPI_HandleTypeDef hspi3;
/**
 * @brief  Inicialización del hardware relacionado con el módulo
 * @param  None
 * @retval None
 */
void InicializoPines(void){

    SetCSPin(1);
    SetWakePin(1);
    SetResetPin(0);
    return;
}

/**
 * @brief  Escribo en el pin destinado a CS
 * @param  Estado de salida - booleano
 * @retval None
 */
void SetCSPin(bool_t estado){

 //   MRF24_CS = estado;
	HAL_GPIO_WritePin(MRF24_CS_GPIO_Port, MRF24_CS_Pin, estado);
    return;
}

/**
 * @brief  Escribo en el pin destinado a Wake
 * @param  Estado de salida - booleano
 * @retval None
 */
void SetWakePin(bool_t estado){

 //   MRF24_WAKE = estado;
	HAL_GPIO_WritePin(MRF24_WAKE_GPIO_Port, MRF24_WAKE_Pin, estado);
    return;
}

/**
 * @brief  Escribo en el pin destinado a Reset
 * @param  Estado de salida - booleano
 * @retval None
 */
void SetResetPin(bool_t estado){

 //   MRF24_RESET = estado;
	HAL_GPIO_WritePin(MRF24_RESET_GPIO_Port, MRF24_RESET_Pin, estado);
    return;
}

/**
 * @brief  Devuelvo el estado del pin interrup del módulo
 * @retval Booleano
 */
bool_t IsMRF24Interrup(void) {

	return HAL_GPIO_ReadPin(MRF24_INTERRUP_GPIO_Port, MRF24_INTERRUP_Pin);
}

/**
 * @brief  Escribo en el puerto SPI
 * @param  Dato - 1 byte
 * @retval None
 */
void WriteByteSPIPort(uint8_t dato){

//    SPIWriteByte(dato);
	HAL_SPI_Transmit(&hspi3, dato, 1, 120);
    return;
}

/**
 * @brief  Escribo en el puerto SPI
 * @param  Dato - 1 byte
 * @retval None
 */
void Write2ByteSPIPort(uint16_t dato){

 //   SPIWrite2Byte(dato);
	HAL_SPI_Transmit(&hspi3, dato, 2, 120);
    return;
}

/**
 * @brief  Leo en el puerto SPI
 * @param  None
 * @retval Dato - 1 byte
 */
uint8_t ReadByteSPIPort(void){

//    return SPIRead();
return 0;
}

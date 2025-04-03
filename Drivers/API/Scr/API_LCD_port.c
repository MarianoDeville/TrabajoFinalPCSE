/*
 * API_LCD_port.c
 *
 *  Created on: Apr 1, 2025
 *      Author: mariano
 */

#include "API_LCD_port.h"

#define LCD_DIR 0X27

extern I2C_HandleTypeDef hi2c3;

void LCDWritePort(uint8_t dato) {

	HAL_I2C_Master_Transmit (&hi2c3, LCD_DIR << 1 , &dato, sizeof(dato), HAL_MAX_DELAY);
}

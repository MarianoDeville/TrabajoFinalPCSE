/*
 * API_LCD_port.h
 *
 *  Created on: Apr 1, 2025
 *      Author: mariano
 */

#ifndef API_INC_API_LCD_port_H_
#define API_INC_API_LCD_port_H_

#include "main.h"

#define DelayLCD(x)	HAL_Delay(x)

void LCDWritePort(uint8_t dato);

#endif /* API_INC_API_LCD_port_H_ */

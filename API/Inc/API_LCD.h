/*
 * API_LCD.h
 *
 *  Created on: Apr 1, 2025
 *      Author: Mariano Deville
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include "main.h"
#include "API_LCD_port.h"




void LCDInint(void);
void LCDWriteCaracter(uint8_t * caracter);
void LCDClear(void);
#endif /* API_INC_API_LCD_H_ */

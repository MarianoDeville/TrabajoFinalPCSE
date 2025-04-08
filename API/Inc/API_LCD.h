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


/* Bits de control por hardware */
#define COMANDO				0x00
#define INFORMACION			0X01
#define ENABLE				0X04
#define BACK_LIGTH			0X08

/* Inicialización */
#define INICIALIZACION_1	0X30
#define INICIALIZACION_2	0X20

/* Control and display command */
#define CLEAR_DISPALY		0X01
#define RETURN_HOME			0X02
#define ENTRY_SET_MODE		0X04
#define INCREASE	 		0X02
#define DISPLAY_IS_SHIFTED	0X01
#define DISPLAY_ON_OFF      0X08
#define DISPLAY_ON 			0X04
#define CURSOR_ON 			0X02
#define BLINKING_ON			0X01
#define SET_FUNCTION		0X20
#define _8_BITS_INTERFACE	0X10
#define _2_LINE_DISPLAY		0X08
#define	_5x10_DOTS			0X04
#define SET_CG_RAM_ADDRESS	0X40
#define SET_DD_RAM_ADDRESS	0X80

#define HIGH_NIBBLE			0XF0
#define LOW_NIBBLE			4



void LCDInint(void);
void LCDWRITECARACTER(const uint8_t * caracter);

#endif /* API_INC_API_LCD_H_ */

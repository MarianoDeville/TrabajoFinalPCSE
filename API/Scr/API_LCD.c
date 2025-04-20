/**
******************************************************************************
 * @file    API_LCD.c
 * @author  Lcdo. Mariano Ariel Deville
 * @brief   Implementación driver display con comunicacion I2C
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
 */

#include "API_LCD.h"

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

static void LCDWrite4Bits(char dato, uint8_t rs);
static void LCDWrite8Bits(char dato, uint8_t rs);

/**
  * @brief  Inicialización del display
  * @retval None
  */
void LCDInint(void) {

	DelayLCD(15);
	LCDWrite4Bits(INICIALIZACION_1, COMANDO);
	DelayLCD(5);
	LCDWrite4Bits(INICIALIZACION_1, COMANDO);
	DelayLCD(1);
	LCDWrite4Bits(INICIALIZACION_2, COMANDO);
	LCDWrite8Bits(DISPLAY_ON_OFF | DISPLAY_ON, COMANDO);
	LCDWrite8Bits(ENTRY_SET_MODE | INCREASE, COMANDO);
	LCDWrite8Bits(SET_FUNCTION | _2_LINE_DISPLAY, COMANDO);
	LCDClear();
	return;
}

/**
  * @brief  Escribo un caracter en el display.
  * @param  Puntero al caracter que voy a escribir.
  * @retval None.
  */
void LCDWriteCaracter(char caracter) {

	LCDWrite8Bits(caracter, INFORMACION);
}

/**
  * @brief	Escribo una cadena en el display.
  * @param  Puntero al caracter que voy a escribir.
  * @retval None.
  */
void LCDWriteString(char * cadena) {

	while(*cadena){

		LCDWriteCaracter(*cadena++);
	}
	return;
}

/**
  * @brief  Limpio la pantalla del display.
  * @retval None.
  */
void LCDClear(void) {

	LCDWrite8Bits(CLEAR_DISPALY, COMANDO);
	DelayLCD(2);
}






/** Funciones privadas
 *
 */


static void LCDWrite4Bits(char dato, uint8_t rs) {

	LCDWritePort(dato | rs | ENABLE | BACK_LIGTH);
	LCDWritePort(dato | rs | BACK_LIGTH);
	return;
}

static void LCDWrite8Bits(char dato, uint8_t rs) {

	LCDWrite4Bits(dato & HIGH_NIBBLE, rs);
	LCDWrite4Bits(dato << LOW_NIBBLE, rs);
	return;
}


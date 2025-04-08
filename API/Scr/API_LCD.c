/*
 * API_LCD.c
 *
 *  Created on: Apr 1, 2025
 *      Author: Mariano Deville
 */

#include "API_LCD.h"

static void LCDWrite4Bits(uint8_t dato, uint8_t rs);
static void LCDWrite8Bits(uint8_t dato, uint8_t rs);

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
	LCDWrite8Bits(CLEAR_DISPALY, COMANDO);
	DelayLCD(5);
	return;
}

static void LCDWrite4Bits(uint8_t dato, uint8_t rs) {

	LCDWritePort(dato | rs | ENABLE | BACK_LIGTH);
	LCDWritePort(dato | rs | BACK_LIGTH);
	return;
}

static void LCDWrite8Bits(uint8_t dato, uint8_t rs) {

	LCDWrite4Bits(dato & HIGH_NIBBLE, rs);
	LCDWrite4Bits(dato << LOW_NIBBLE, rs);
	return;
}

void LCDWRITECARACTER(const uint8_t * caracter) {

	LCDWrite8Bits(caracter, INFORMACION);
}


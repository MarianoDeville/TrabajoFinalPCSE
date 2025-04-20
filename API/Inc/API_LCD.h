/**
******************************************************************************
 * @file    API_LCD.h
 * @author  Lcdo. Mariano Ariel Deville
 * @brief   Archivo cabecera para la implementación driver display con
 * 			comunicacion I2C
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
 */
#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include "main.h"
#include "API_LCD_port.h"




void LCDInint(void);
void LCDWriteCaracter(char caracter);
void LCDWriteString(char * cadena);
void LCDClear(void);



#endif /* API_INC_API_LCD_H_ */

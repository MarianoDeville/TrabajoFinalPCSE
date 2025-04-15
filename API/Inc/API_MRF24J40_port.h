/*
 * API_MRF24J40_port.h
 *
 *  Created on: Apr 9, 2025
  *      Author: Mariano Deville
 */

#ifndef INC_API_MRF24J40_PORT_H_
#define INC_API_MRF24J40_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "drv_mspi_port.h"
//#include "../../redef_var.h"



/* Prototipo de funciones públicas -------------------------------------------*/
void InicializoPines(void);
void SetCSPin(bool_t estado);
void SetWakePin(bool_t estado);
void SetResetPin(bool_t estado);
bool_t IsMRF24Interrup(void);
void WriteByteSPIPort(uint8_t dato);
void Write2ByteSPIPort(uint16_t dato);
uint8_t ReadByteSPIPort(void);

#endif /* INC_API_MRF24J40_PORT_H_ */

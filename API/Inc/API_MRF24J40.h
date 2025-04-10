/*
 * API_MRF24J40.h
 *
 *  Created on: Apr 9, 2025
 *      Author: Mariano Deville
 */

#ifndef INC_API_MRF24J40_H_
#define INC_API_MRF24J40_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "../../redef_var.h"

/* Prototipo de funciones públicas -------------------------------------------*/
void MRF24J40Init(void);
void EnviarDato(void);
void EnviarComando();
void EnviarDatoEncriptado(void);
void ReciboPaquete(void);
void BuscarDispositivos(void);
void SetMensajeSalida(const char * mensaje);
void SetDireccionDestino(uint16_t direccion);
void SetPANIDDestino(uint16_t panid);

#endif /* INC_API_MRF24J40_H_ */

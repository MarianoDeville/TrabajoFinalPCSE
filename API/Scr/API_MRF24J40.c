/**
******************************************************************************
 * @file    DriverMRF24J40.X/drivers/src/drv_mrf24j40.c
 * @author  Lcdo. Mariano Ariel Deville
 * @brief   Implementación driver módulo MRF24J40MA
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "API_MRF24J40.h"
#include "API_MRF24J40_port.h"
#include "compatibility.h"

/* Definiciones de la configuración por defecto ------------------------------*/
#define	DEFAULT_CHANNEL     CH_11
#define DEFAULT_SEC_NUMBER  0X01
#define	MY_DEFAULT_PAN_ID	0x1234
#define	MY_DEFAULT_ADDRESS	0xDE11

#define HEAD_LENGTH         0X0E
#define WRITE_16_BITS       0X8010
#define READ_16_BITS        0X8000
#define WRITE_8_BITS        0x01
#define READ_8_BITS         0x7E

/* Variables privadas --------------------------------------------------------*/
/* MAC address por defecto del dispositivo */
static const uint8_t default_mac_address[] = {0x11,
                                             0x28,
                                             0x35,
                                             0x44,
                                             0x56,
                                             0x66,
                                             0x77,
                                             0x01};

/* Security key por defecto del dispositivo */
static const uint8_t default_security_key[] = {0x00,
                                               0x10,
                                               0x25,
                                               0x37,
                                               0x04,
                                               0x55,
                                               0x06,
                                               0x79,
                                               0x08,
                                               0x09,
                                               0x10,
                                               0x11,
                                               0x12,
                                               0x13,
                                               0x14,
                                               0x15};


/* Estructura con la información del dispositivo */
static struct {

    bool_t get_new_msg;
    bool_t put_new_msg;
    uint8_t sequence_number;
    uint8_t my_channel;
    uint8_t security_key[16];
    uint8_t my_mac[8];
    uint16_t my_panid;
    uint16_t my_address;
    uint16_t intervalo;
}mrf24_data_config;

/* Estructura con la información de transmisión */
static struct {

    uint16_t destinity_panid;
    uint16_t destinity_address;
    uint8_t largo_mensaje;
    const char * buffer_salida;
}mrf24_data_out;

/* Estructura con la información de recepción */
static struct {

    uint16_t source_panid;
    uint16_t source_address;
    uint8_t tamano_mensaje;
    unsigned char buffer_entrada[50];
}mrf24_data_in;

/* Canales disponibles para el IEEE 802.15.4 */
typedef enum {

    CH_11 = 0x03,
    CH_12 = 0x13,
    CH_13 = 0x23,
	CH_14 = 0x33,
	CH_15 = 0x43,
	CH_16 = 0x53,
	CH_17 = 0x63,
	CH_18 = 0x73,
	CH_19 = 0x83,
	CH_20 = 0x93,
	CH_21 = 0xA3,
	CH_22 = 0xB3,
	CH_23 = 0xC3,
	CH_24 = 0xD3,
	CH_25 = 0xE3,
	CH_26 = 0xF3
}channel_list;

enum {
    EADR0 = 0x05,
    EADR1,
    EADR2,
    EADR3,
    EADR4,
    EADR5,
    EADR6,
    EADR7,
} my_default_mac_address;

/* Macros --------------------------------------------------------------------*/
#define VACIO           0X00
/* Short address registers for reading */
#define	RXMCR			(0x00)
#define	PANIDL			(0x01)
#define	PANIDH			(0x02)
#define	SADRL			(0x03)
#define	SADRH			(0x04)
#define	RXFLUSH			(0x0D)
#define	ORDER			(0x10)
#define	TXMCR			(0x11)
#define	ACKTMOUT		(0x12)
#define	ESLOTG1			(0x13)
#define	SYMTICKL		(0x14)
#define	SYMTICKH		(0x15)
#define	PACON0			(0x16)
#define	PACON1			(0x17)
#define	PACON2			(0x18)
#define	TXBCON0			(0x1A)
#define	TXNCON			(0x1B)
#define	TXG1CON			(0x1C)
#define	TXG2CON			(0x1D)
#define	ESLOTG23		(0x1E)
#define	ESLOTG45		(0x1F)
#define	ESLOTG67		(0x20)
#define	TXPEND			(0x21)
#define	WAKECON			(0x22)
#define	FRMOFFSET		(0x23)
#define	TXSTAT			(0x24)
#define	TXBCON1			(0x25)
#define	GATECLK			(0x26)
#define	TXTIME			(0x27)
#define	HSYMTMRL		(0x28)
#define	HSYMTMRH		(0x29)
#define	SOFTRST			(0x2A)
#define	SECCON0			(0x2C)
#define	SECCON1			(0x2D)
#define	TXSTBL			(0x2E)
#define	RXSR			(0x30)
#define	INTSTAT			(0x31)
#define MRFINTCON       (0x32)
#define	GPIO			(0x33)
#define	TRISGPIO		(0x34)
#define	SLPACK			(0x35)
#define	RFCTL			(0x36)
#define	SECCR2			(0x37)
#define	BBREG0			(0x38)
#define	BBREG1			(0x39)
#define	BBREG2			(0x3A)
#define	BBREG3			(0x3B)
#define	BBREG4			(0x3C)
#define	BBREG6			(0x3E)
#define	CCAEDTH			(0x3F)
/* Long address registers  */
#define	RFCON0			(0x200)
#define	RFCON1			(0x201)
#define	RFCON2			(0x202)
#define	RFCON3			(0x203)
#define	RFCON5			(0x205)
#define	RFCON6			(0x206)
#define	RFCON7			(0x207)
#define	RFCON8			(0x208)
#define	SLPCAL0			(0x209)
#define	SLPCAL1			(0x20a)
#define	SLPCAL2			(0x20b)
#define	RFSTATE			(0x20f)
#define	RSSI			(0x210)
#define	SLPCON0			(0x211)
#define	SLPCON1			(0x220)
#define	WAKETIMEL		(0x222)
#define	WAKETIMEH		(0x223)
#define	REMCNTL			(0x224)
#define	REMCNTH			(0x225)
#define	MAINCNT0		(0x226)
#define	MAINCNT1		(0x227)
#define	MAINCNT2		(0x228)
#define	MAINCNT3		(0x229)
#define	TESTMODE		(0x22f)
#define	ASSOEADR0		(0x230)
#define	ASSOEADR1		(0x231)
#define	ASSOEADR2		(0x232)
#define	ASSOEADR3		(0x233)
#define	ASSOEADR4		(0x234)
#define	ASSOEADR5		(0x235)
#define	ASSOEADR6		(0x236)
#define	ASSOEADR7		(0x237)
#define	ASSOSADR0		(0x238)
#define	ASSOSADR1		(0x239)
#define	UPNONCE0		(0x240)
#define	UPNONCE1		(0x241)
#define	UPNONCE2		(0x242)
#define	UPNONCE3		(0x243)
#define	UPNONCE4		(0x244)
#define	UPNONCE5		(0x245)
#define	UPNONCE6		(0x246)
#define	UPNONCE7		(0x247)
#define	UPNONCE8		(0x248)
#define	UPNONCE9		(0x249)
#define	UPNONCE10		(0x24A)
#define	UPNONCE11		(0x24B)
#define	UPNONCE12		(0x24C)
/* Definitions for FIFOs in the memory */
#define	TX_NORMAL_FIFO	(0x000)
#define	TX_BEACON_FIFO	(0x080)
#define	TX_GTS1_FIFO	(0x100)
#define	TX_GTS2_FIFO	(0x180)
#define	RX_FIFO			(0x300)
#define	TX_SEC_KEY		(0x280)
#define RX_SEC_KEY		(0x2B0)
/* Configuraciones de la transmisión */
#define	BROADCAST		(0xFFFF)
#define SEG_HAB			(0X02)
#define ESPERO_ACK		(0X04)
#define	P30dBm			(0XC0)
#define	P20dBm			(0X80)
#define	P10dBm			(0X40)
#define	P6_3dBm			(0X38)
#define	P4_9dBm			(0X30)
#define	P3_7dBm			(0X28)
#define	P2_8dBm			(0X20)
#define	P1_9dBm			(0X18)
#define	P1_2dBm			(0X10)
#define	P0_5dBm			(0X08)
#define	P0dBm			(0X00)
/* LSB */
#define	DATA			(0X01)
#define	ACK				(0X02)
#define	MAC_COMM		(0X03)
#define	SECURITY		(0X08)
#define	FRAME_PEND		(0X10)
#define	ACK_REQ			(0X20)
#define	INTRA_PAN		(0X40)
/* MSB */
#define TX_CTR			(0x01)
#define TX_CCM128		(0x02)
#define TX_CCM64		(0x03)
#define TX_CCM32		(0x04)
#define TX_CBC_MAC128	(0x05)
#define TX_CBC_MAC64	(0x06)
#define TX_CBC_MAC32	(0x07)
#define	SHORT_D_ADD		(0X08)
#define	LONG_D_ADD		(0X0C)
#define	SHORT_S_ADD		(0X80)
#define	LONG_S_ADD		(0XC0)

/* Prototipo de funciones privadas -------------------------------------------*/
static void InicializoVariables(void);
static void SetShortAddr(uint8_t reg_address, uint8_t value);
static void SetLongAddr(uint16_t reg_address, uint8_t value);
static uint8_t GetShortAddr(uint8_t reg_address);
static uint8_t GetLongAddr(uint16_t reg_address);
static void SetDeviceAddress(void);
static void SetChannel(void);
static void SetDeviceMACAddress(void);

/**
 * @brief  Inicialización del módulo MRF24J40MA
 * @param  None
 * @retval None
 */
void MRF24J40Init(void) {

    uint8_t lectura;
    InicializoVariables();
    InicializoPines();
    delay_t(1);
    SetResetPin(1);
    delay_t(1);
GetShortAddr(0x00);
    SetShortAddr(SOFTRST,0x07);

    do {
        lectura = GetShortAddr(SOFTRST);
    }while((lectura&0x07) != VACIO);
    delay_t(1);
    SetShortAddr(RXFLUSH, 0x01);
    SetDeviceAddress();
    SetDeviceMACAddress();
    SetLongAddr(RFCON2, 0x80);
    SetLongAddr(RFCON3, P30dBm | P6_3dBm);
	SetLongAddr(RFCON6, 0x90);
	SetLongAddr(RFCON7, 0x80);
	SetLongAddr(RFCON8, 0x10);
	SetLongAddr(SLPCON1, 0x21);
    SetShortAddr(BBREG2, 0x80);
    SetShortAddr(BBREG6, 0x40);
    SetShortAddr(CCAEDTH, 0x60);
    SetShortAddr(PACON2, 0x98);
    SetShortAddr(TXSTBL, 0x95);

    do {
		lectura = GetLongAddr(RFSTATE);
	}while((lectura & 0xA0) != 0xA0);
    SetShortAddr(MRFINTCON, 0xE6);
	SetShortAddr(ACKTMOUT, 0xB9);
    SetLongAddr(RFCON0, 0x03);
	SetLongAddr(RFCON1, 0x02);
	SetChannel();
    /* TURBO_MODE si es necesario mayor ancho de banda, máximo 625 Kbps */
#ifdef TURBO_MODE
	SetShortAddr(BBREG0,0x01);
	SetShortAddr(BBREG3,0x38);
	SetShortAddr(BBREG4,0x5C);
	SetShortAddr(RFCTL,0x04);
	SetShortAddr(RFCTL,0x00);
#endif
	SetShortAddr(RXMCR,0x00);
	return;
}

/* Funciones privadas --------------------------------------------------------*/
/**
 * @brief  Inicialización de variables de configuración por defecto.
 * @param  None
 * @retval None
 */
static void InicializoVariables(void) {

    for(int i = 0; i < 16; i++){

        if(i < 8)
            mrf24_data_config.my_mac[i] = default_mac_address[i];
        mrf24_data_config.security_key[i] = default_security_key[i];
    }
    mrf24_data_config.sequence_number = DEFAULT_SEC_NUMBER;
    mrf24_data_config.my_channel = DEFAULT_CHANNEL;
    mrf24_data_config.get_new_msg = false;
    mrf24_data_config.put_new_msg = false;
    mrf24_data_config.my_panid = MY_DEFAULT_PAN_ID;
    mrf24_data_config.my_address = MY_DEFAULT_ADDRESS;
    mrf24_data_in.source_address = VACIO;
    mrf24_data_in.source_panid = VACIO;
    mrf24_data_in.tamano_mensaje = VACIO;
    mrf24_data_in.buffer_entrada[0] = VACIO;
    return;
}

/**
 * @brief  Escribo de en registro de 1 byte un dato de 1 byte
 * @param  Dirección del registro - 1 byte, dato - 1 byte
 * @retval None
 */
static void SetShortAddr(uint8_t reg_address, uint8_t value) {

    reg_address = (uint8_t) (reg_address << 1) | WRITE_8_BITS;
    SetCSPin(false);
	WriteByteSPIPort(reg_address);
	WriteByteSPIPort(value);
    SetCSPin(true);
	return;
}

/**
 * @brief  Leo en registro de 1 byte un dato de 1 byte
 * @param  Dirección del registro - 1 byte, dato - 1 byte
 * @retval Valor devuelto por el módulo - 1 byte
 */
static uint8_t GetShortAddr(uint8_t reg_address) {

   	uint8_t leido_spi = VACIO;
    reg_address = (uint8_t) (reg_address << 1) & READ_8_BITS;
    SetCSPin(false);
    WriteByteSPIPort(reg_address);
    leido_spi = ReadByteSPIPort();
    SetCSPin(true);
	return leido_spi;
}

/**
 * @brief  Escribo de en registro de 2 bytes un dato de 1 byte
 * @param  Dirección del registro - 2 bytes, dato - 1 byte
 * @retval None
 */
static void SetLongAddr(uint16_t reg_address, uint8_t value) {

    reg_address = (reg_address << 5) | WRITE_16_BITS;
    SetCSPin(false);
    Write2ByteSPIPort(reg_address);
	WriteByteSPIPort(value);
    SetCSPin(true);
	return;
}

/**
 * @brief  Leo en registro de 2 bytes un dato de 1 byte
 * @param  Dirección del registro - 2 bytes, dato - 1 byte
 * @retval Valor devuelto por el módulo - 1 byte
 */
static uint8_t GetLongAddr(uint16_t reg_address) {

	uint8_t respuesta;
    reg_address = (reg_address << 5) | READ_16_BITS;
    SetCSPin(false);
    Write2ByteSPIPort(reg_address);
	respuesta = ReadByteSPIPort();
    SetCSPin(true);
	return respuesta;
}

/**
 * @brief  Seteo en el módulo en canal guardado en mrf24_data_config
 * @param  None
 * @retval None
 */
static void SetChannel(void) {

	SetLongAddr(RFCON0, mrf24_data_config.my_channel);
	SetShortAddr(RFCTL, 0x04);
	SetShortAddr(RFCTL, 0x00);
	delay_t(1);
	return;
}

/**
 * @brief  Seteo en el módulo la dirección corta guardada en mrf24_data_config
 * @param  None
 * @retval None
 */
static void SetDeviceAddress(void) {

	SetShortAddr(SADRH, (uint8_t) (mrf24_data_config.my_address >> 8));
	SetShortAddr(SADRL, (uint8_t) (mrf24_data_config.my_address));
	SetShortAddr(PANIDH, (uint8_t) (mrf24_data_config.my_panid >> 8));
	SetShortAddr(PANIDL, (uint8_t) (mrf24_data_config.my_panid));
	return;
}

/**
 * @brief  Seteo en el módulo la dirección mac guardada en mrf24_data_config
 * @param  None
 * @retval None
 */
static void SetDeviceMACAddress(void) {

    my_default_mac_address = EADR0;

    for(int i = 0; i < 8; i++) {

        SetShortAddr(my_default_mac_address++, mrf24_data_config.my_mac[i]);
    }
	return;
}

/* Funciones públicas --------------------------------------------------------*/

/**
 * @brief
 * @param  None
 * @retval None
 */
void SetMensajeSalida(const char * mensaje) {

    mrf24_data_out.buffer_salida = mensaje;
    mrf24_data_out.largo_mensaje = (uint8_t) strlen(mensaje);
    return;
}

/**
 * @brief
 * @param  None
 * @retval None
 */
void SetDireccionDestino(uint16_t direccion) {

    mrf24_data_out.destinity_address = direccion;
    return;
}

/**
 * @brief
 * @param  None
 * @retval None
 */
void SetPANIDDestino(uint16_t panid) {

    mrf24_data_out.destinity_panid = panid;
    return;
}

/**
 * @brief  Envío la información almacenada en la estructura de salida
 * @param  None
 * @retval None
 */
void EnviarDato(void) {

	uint8_t pos_memoria = 0;
	uint8_t largo_cabecera = HEAD_LENGTH;
	SetLongAddr(pos_memoria++, largo_cabecera);
	SetLongAddr(pos_memoria++, mrf24_data_out.largo_mensaje + largo_cabecera);
	SetLongAddr(pos_memoria++, DATA|ACK_REQ|INTRA_PAN);         // LSB.
	SetLongAddr(pos_memoria++, LONG_S_ADD|SHORT_D_ADD);         // MSB.
	SetLongAddr(pos_memoria++, mrf24_data_config.sequence_number++);
	SetLongAddr(pos_memoria++, (uint8_t) mrf24_data_out.destinity_panid);
	SetLongAddr(pos_memoria++, (uint8_t) (mrf24_data_out.destinity_panid >> 8));
	SetLongAddr(pos_memoria++, (uint8_t) mrf24_data_out.destinity_address);
	SetLongAddr(pos_memoria++, (uint8_t) (mrf24_data_out.destinity_address >> 8));

    for(int8_t i = 0; i < mrf24_data_out.largo_mensaje; i++) {

		SetLongAddr(pos_memoria++, mrf24_data_out.buffer_salida[i]);
	}
	SetShortAddr(TXNCON, 1 | ESPERO_ACK);               // Realizo el envio.
	return;
}














/**
 * @brief  Envío la información almacenada en la estructura de salida encriptada
 * @param  None
 * @retval None
  ******************************************************************************
 * @attention
 *					 LSB.
 *	DATA | ACK | MAC_COMM | SECURITY | FRAME_PEND | ACK_REQ | INTRA_PAN
 *					 MSB.
 *	SHORT_D_ADD | LONG_D_ADD | SHORT_S_ADD | LONG_S_ADD
  ******************************************************************************
 */
void EnviarDatoEncriptado(void) {

	uint16_t pos_memoria = 0;
	SetLongAddr(pos_memoria++, 0X15);                                               // Longitud de la cabecera.
	SetLongAddr(pos_memoria++, 0X15 + 0X0B + 5);                                    // Longitud del paquete.
	SetLongAddr(pos_memoria++, DATA|ACK_REQ|INTRA_PAN | SECURITY);      // LSB.
	SetLongAddr(pos_memoria++, LONG_S_ADD | SHORT_D_ADD);               // MSB.
	SetLongAddr(pos_memoria++, mrf24_data_config.sequence_number++);
	SetLongAddr(pos_memoria++, (uint8_t) (mrf24_data_out.destinity_panid));
	SetLongAddr(pos_memoria++, (uint8_t) (mrf24_data_out.destinity_panid >> 8));

	SetLongAddr(pos_memoria++, 0x01);
	SetLongAddr(pos_memoria++, 0x00);
	SetLongAddr(pos_memoria++, 0x00);
	SetLongAddr(pos_memoria++, 0x00);
	SetLongAddr(pos_memoria++, 0x00);			// Mi número de clave.

	for(uint16_t i = 0; i < 16; i++) {

		SetLongAddr(TX_SEC_KEY + i, mrf24_data_config.security_key[i + 1]);
	}
	SetLongAddr(SECCON0, 0x04);			// Suit de encriptación.

	for(uint16_t i = 0; i < mrf24_data_out.largo_mensaje; i++) {

		SetLongAddr(pos_memoria++, *mrf24_data_out.buffer_salida++);
	}
	SetShortAddr(TXNCON, 0x07);			// Realizo el envio.
	return;
}



/**
 * @brief  Envío un comando almacenado en la estructura de salida
 * @param  None
 * @retval None
  ******************************************************************************
 * @attention
 *					 LSB.
 *	DATA | ACK | MAC_COMM | SECURITY | FRAME_PEND | ACK_REQ | INTRA_PAN
 *					 MSB.
 *	SHORT_D_ADD | LONG_D_ADD | SHORT_S_ADD | LONG_S_ADD
  ******************************************************************************
 */
void EnviarComando(void) {

	uint8_t pos = 0;
	uint16_t i;
	SetLongAddr(pos++, 0x0f);			// Longitud de la cabecera.
	SetLongAddr(pos++, 0x13);			//
	SetLongAddr(pos++, 0x43);			// LSB.
	SetLongAddr(pos++, 0xc8);			// MSB.
	SetLongAddr(pos++, mrf24_data_config.sequence_number++);
	SetLongAddr(pos++, (uint8_t) mrf24_data_out.destinity_panid);
	SetLongAddr(pos++, (uint8_t) (mrf24_data_out.destinity_panid >> 8));
	SetLongAddr(pos++, (uint8_t) mrf24_data_out.destinity_address);
	SetLongAddr(pos++, (uint8_t) (mrf24_data_out.destinity_address >> 8));
	for(i = 0; i < 8; i++)					// MAC address de origen.
	{
		SetLongAddr(pos++, mrf24_data_config.my_mac[i]);
	}
	SetLongAddr(pos++, 0x81);
	SetLongAddr(pos++, 0x18);
	SetLongAddr(pos++, 0x09);
	SetLongAddr(pos++, 0x01);
//	SetShortAddr(TXNCON, SEG_HAB|1);		// Realizo el envio.
	SetShortAddr(TXNCON, 1 | ESPERO_ACK);	// Realizo el envio.
	return;
}

/**
 * @brief  Recibir un paquete y dejarlo en el bufer de entrada de mrf24_data_config
 * @param  None
 * @retval None
 */
void ReciboPaquete(void) {//////////////////////////////////////////////////////////// para que obtengo el rssi?

	uint8_t i;
	uint8_t rssi,final;
	final = GetLongAddr(RX_FIFO);		// Obtengo la longitud del mensaje.
	for(i = 0; i < final - 17; i++)
	{
		mrf24_data_in.buffer_entrada[i] = GetLongAddr(RX_FIFO + i + 16);
	}
	mrf24_data_in.buffer_entrada[i] = 0;    // Marco el final de la cadena.
	rssi = GetLongAddr(RSSI);		// Calidad de la señal.
	return;
}

/**
 * @brief  Buscar dispositivos en la cercanía
 * @param  None
 * @retval None
 */
void BuscarDispositivos(void) {                                                    // acá debería devolver una estructura con los dispositivos encontrados

//	SetChannel(DEF_CH);
//	Envio_Dato(0x1234,BROADCAST,rs_str);
	return;
}

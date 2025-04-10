# TrabajoFinalPCSE

	Trabajo final para la materia protocolos de comunicación de la carrera especialización en sistemas embebidos.

Objetivos
	
	Implementar drivers portables para los dispositivos (Display, Transceiver MRF24J40) conectados a la placa de desarrollo NUCLEO-F446RE.
	Implementar una máquina de estados finitos.
	Comunicar dos placas por medio de un transceiver inhalámbrico, con comunicación bidireccional.
	

Estructura del proyecto

TrabajoFinalPCSE
	├── /API
	│	├── /Inc
    │	│   ├── API_debounce.h
    │	│   ├── API_delay.h
    │	│   ├── API_LCD_port.h
    │	│   ├── API_LCD.h
    │	│   ├── API_MRF24J40_port.h
    │	│   ├── API_MRF24J40.h
    │	│   └── API_UART.h
    │	└── /Src
    │	    ├── API_debounce.c
    │	    ├── API_delay.c
    │	    ├── API_LCD_port.c
    │	    ├── API_LCD.c
    │	    ├── API_MRF24J40_port.c
    │	    ├── API_MRF24J40.c
    │	    └── API_UART.c
    ├── /Core
	│	├── /Inc    
    │	│   └── main.h    
    │	└── /Src
    │	    └── main.c
	└── /Drivers


Debounce API




Delay API

    
    
    
LCD API




    
UART API




MRF24J40 API





Requirimientos



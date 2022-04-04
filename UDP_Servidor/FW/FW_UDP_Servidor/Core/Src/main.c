/**
**************************************************************************************
\file          main.c
\brief         Archivo principal del ejemplo Firmware para implementar un Servidor UDP
 	 	 	   simple en microcontrolador STM32F4 haciendo uso del stack lwIP.

\details	   Se ha desarrollado una aplicación simple en el callback de recpecion
 	 	 	   del servidor para controlar los 4 leds de la tarjeta STM32F4 Discovery.

			   Sobre las conexiones y configuración se recomienda leer:
			   - Conexiones.pdf
			   - Inicializado.pdf

			   Es recomendable usar el software Hercules para testear el servidor
			   enviando y recibiendo paquetes de datos.

\author        Juan Galbis Domènech
\version       1.0
\date          30/03/2022
**************************************************************************************/

#include "main.h"
#include "Init_HW.h"
#include "lwip.h"
#include "udpServerRAW.h"

extern struct netif gnetif;


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  Init_HW();
  LWIP_Init();						//Declarar aqui IP, Mascara Subred y Puerta de Enlace del Servidor (Microcontrolador)
  udpServer_init();					//Declarar aqui IP del cliente (PC)

  while (1)
  {
	  ethernetif_input(&gnetif);
	  sys_check_timeouts();
  }

}

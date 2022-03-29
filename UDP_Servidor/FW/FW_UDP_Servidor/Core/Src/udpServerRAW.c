/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  udpServerRAW.c
  Author:     ControllersTech.com
  Updated:    Jul 23, 2021

  ***************************************************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ***************************************************************************************************************
*/


#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#include "stdio.h"
#include <string.h>
#include <Test_Servidor.h>
#include "udpServerRAW.h"

#include "stdlib.h"

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);


/* IMPLEMENTATION FOR UDP Server :   source:https://www.geeksforgeeks.org/udp-server-client-implementation-c/

1. Create UDP socket.
2. Bind the socket to server address.
3. Wait until datagram packet arrives from client.
4. Process the datagram packet and send a reply to client.
5. Go back to Step 3.
*/

void udpServer_init(void)
{
	// UDP Control Block structure
   struct udp_pcb *upcb;
   err_t err;

   /* 1. Create a new UDP control block  */
   upcb = udp_new();

   /* 2. Bind the upcb to the local port */
   ip_addr_t myIPADDR;
   IP_ADDR4(&myIPADDR, 172, 25, 144, 126);

   err = udp_bind(upcb, &myIPADDR, 7);  // 7 is the server UDP port


   /* 3. Set a receive callback for the upcb */
   if(err == ERR_OK)
   {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else
   {
	   udp_remove(upcb);
   }
}

// udp_receive_callback will be called, when the client sends some data to the server
/* 4. Process the datagram packet and send a reply to client. */

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	struct pbuf *txBuf;

	//JGD convierte a string la IP del cliente UDP que envia los datos, puede servir para implementar un filtro previo para que solo acepte peticiones determiandas IPs
	//char *remoteIP = ipaddr_ntoa(addr);

	char buf[256];												//Almacena datos recibidos
	char tx_buf[6];

	int len = sprintf (buf,"%s", (char*)p->payload);			//Obtiene numero de bytes recibido

	//INICIA APLICACION

	if(Gestion_Datos_Servidor_UPD(len, &buf)==1){				//Si la accion SI existe en el diccionario el servidor devuelve OK
		 tx_buf[0] = 'O'; tx_buf[1] = 'K';
		 tx_buf[2] = '\n';
	}else{
		 tx_buf[0] = 'E'; tx_buf[1] = 'R';						//Si la accion NO existe en el diccionario el servidor devuelve ERRROR
		 tx_buf[2] = 'R'; tx_buf[3] = 'O';
		 tx_buf[4] = 'R'; tx_buf[5] = '\n';
	}

	//DEVUELVE RESPUESTA

	/* allocate pbuf from RAM*/
	txBuf = pbuf_alloc(PBUF_TRANSPORT,len, PBUF_RAM);

	/* copy the data into the buffer  */
	pbuf_take(txBuf, tx_buf, len);

	/* Connect to the remote client */
	udp_connect(upcb, addr, port);

	/* Send a Reply to the Client */
	udp_send(upcb, txBuf);

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb);

	/* Free the p_tx buffer */
	pbuf_free(txBuf);

	/* Free the p buffer */
	pbuf_free(p);

    memset(tx_buf, 0, len);										//Borra cadena de respuesta para siguiente peticion

}


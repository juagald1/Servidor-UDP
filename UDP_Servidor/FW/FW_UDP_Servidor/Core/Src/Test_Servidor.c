/*
 * Test_Servidor.c
 *
 *  Created on: Mar 29, 2022
 *      Author: jugaldo
 */

#include "string.h"
#include "stm32f4xx_hal.h"


int Gestion_Datos_Servidor_UPD (int longitud, char* str)
{
	char string[longitud];						//Recibe hasta 1 Byte
	strcpy(string, str);						//Copia datos recibidos en buffer a la cadena

	////////////////////////////////////
	//  DESARROLLO APLICACION AQUI   //
	///////////////////////////////////

	if(strcmp(string,"LED1_ON") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
		  return 1;
	}

	if(strcmp(string,"LED1_OFF") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
		  return 1;
	}

	if(strcmp(string,"LED2_ON") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
		  return 1;
	}

	if(strcmp(string,"LED2_OFF") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
		  return 1;
	}

	if(strcmp(string,"LED3_ON") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		  return 1;
	}

	if(strcmp(string,"LED3_OFF") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		  return 1;
	}

	if(strcmp(string,"LED4_ON") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		  return 1;
	}

	if(strcmp(string,"LED4_OFF") == 0)
	{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		  return 1;
	}

	  return 0;
}


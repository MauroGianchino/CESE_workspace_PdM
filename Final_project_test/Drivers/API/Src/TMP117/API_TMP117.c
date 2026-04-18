/*
 * API_TMP117.c
 *
 *  Created on: 9 abr 2026
 *      Author: Mauro
 */

#include "API_TMP117.h"


#define SENSOR_ADDR (0x49 << 1) // Dirección 0x49 desplazada
#define ID_ADDR 0x0F // Registro de device ID
#define TEMP_ADDR 0X00 // Registro para leer la temperatura

bool TMP117_readTemperature(float *temp){

	if(temp == NULL)
	{
		return false;
	}
	uint8_t data[2];
	uint16_t device_temp = 0;
	float actual_temp = 0;
	bool status;
	HAL_GPIO_WritePin(GPIOA, XLAT_Pin, GPIO_PIN_RESET);
	status = readRegister(SENSOR_ADDR, TEMP_ADDR,data);

	if (status == true)
	{
		  		  device_temp = (data[0] << 8) | data[1]; //debo hacer un desplazamiento de 8 posiciones porque el primer byte que se recibe es el MSB y luego hago una OR con el segundo byte (data[1])
		  		  actual_temp = (float)device_temp * 0.0078125f; //casteo a float para multiplicar por la resolucion (indicado por hoja de datos)
		  		  *temp = actual_temp;
		  		  return true;
	}
	else
	{
		return false;
	}

}

bool TMP117_readID(uint16_t *id){

	if(id == NULL)
	{
		return false;
	}
	uint8_t data[2];
	uint16_t device_id = 0;
	uint16_t actual_id = 0;
	bool status;

	status = readRegister(SENSOR_ADDR, ID_ADDR,data); //leo el ID del sensor y se almacena en data

	if (status == true)
	{
		device_id = (data[0] << 8) | data[1]; //debo hacer un desplazamiento de 8 posiciones porque el primer byte que se recibe es el MSB y luego hago una OR con el segundo byte (data[1])
		actual_id = device_id & 0x0FFF; //se enmascara con 12 bits porque el address son los 12 bits LSB, los bits 15 a 12 estan reservados
		*id = actual_id;
		return true;
	}
	else
	{
		return false;
	}


}

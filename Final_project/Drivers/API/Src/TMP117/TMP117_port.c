/*
 * TMP117_port.c
 *
 *  Created on: 10 abr 2026
 *      Author: mgianchino
 */


#include "TMP117_port.h"

#define I2C_TIMEOUT 100

#define SIZE_REGISTER 2

#define SIZE_ADDRESS_REGISTER 1

extern I2C_HandleTypeDef hi2c1;


bool readRegister(uint16_t address, uint8_t regAddress, uint8_t *pData)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Master_Transmit(&hi2c1, address, &regAddress,
	SIZE_ADDRESS_REGISTER,
	I2C_TIMEOUT);

	if (status == HAL_OK)
	{
		status = HAL_I2C_Master_Receive(&hi2c1, address, pData, SIZE_REGISTER,
		I2C_TIMEOUT); // Timeout de 100ms
		if (status == HAL_OK)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}

	/*status = HAL_I2C_Mem_Read(&hi2c1, DevAddress, MemAddress,
	 I2C_MEMADD_SIZE_8BIT, pData, SIZE, I2C_TIMEOUT);*/

}

bool writeRegister(uint16_t address, uint8_t regAddress, uint16_t data)
{
	HAL_StatusTypeDef status;

	uint8_t buffer[3];

	buffer[0] = regAddress;

	buffer[1] = (uint8_t) (data >> 8);

	buffer[2] = (uint8_t) (data & 0xFF);

	status = HAL_I2C_Master_Transmit(&hi2c1, address, buffer, 3,
	I2C_TIMEOUT);

	if (status == HAL_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

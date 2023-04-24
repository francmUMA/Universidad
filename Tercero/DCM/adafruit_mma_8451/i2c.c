#include "i2c.h"

/*
HAL_I2C_Master_Transmit

Function Name                   HAL_StatusTypeDef HAL_I2C_Master_Transmit (I2C_HandleTypeDef * hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
Function Description            Transmits in master mode an amount of data in blocking mode.
Parameters  hi2c: :            Pointer to a I2C_HandleTypeDef structure that contains the configuration information for the specified I2C.
DevAddress:                     Target device address
pData:                          Pointer to data buffer
Size:                           Amount of data to be sent
Timeout:                        Timeout duration
Return values HAL status
*/

void write_register(uint8_t reg, uint16_t value, I2C_HandleTypeDef hi2c1){
    uint8_t data[3];                    //[0] = reg, [1] = MSB, [2] = LSB
    data[0] = reg;
    data[1] = (value >> 8) & 0xFF;      //MSB
    data[2] = value & 0xFF;             //LSB

    if (HAL_I2C_Master_Transmit(&hi2c1, MMA8451_DEFAULT_ADDRESS, data, 3, HAL_MAX_DELAY) != HAL_OK){
        // Error handler
        printf("Error writing register\n");
    }
}

uint8_t *read_register(uint8_t reg, I2C_HandleTypeDef hi2c1){
    uint8_t data[2];       //[0] = MSB, [1] = LSB

    //Indicamos de qué registro queremos leer
    if (HAL_I2C_Master_Transmit(&hi2c1, MMA8451_DEFAULT_ADDRESS, &reg, 1, HAL_MAX_DELAY) != HAL_OK){
        // Error handler
        printf("Error writing register\n");
    }

    //Leemos el valor del registro
    if (HAL_I2C_Master_Receive(&hi2c1, MMA8451_DEFAULT_ADDRESS, data, 2, HAL_MAX_DELAY) != HAL_OK){
        // Error handler
        printf("Error reading register\n");
    }

    return data;
}
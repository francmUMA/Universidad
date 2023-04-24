#include "MMA_8451.h"

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

void init_MMA8451(I2C_HandleTypeDef hi2c1){
    //Inicialización del acelerómetro
    write_register(MMA8451_REG_CTRL_REG2, 0x40, hi2c1);     //Reset

    // Espera a que se resetee
    while (read_register(MMA8451_REG_CTRL_REG2, hi2c1)[1] & 0x40);

    // Se establece de rango 4G
    write_register(MMA8451_REG_XYZ_DATA_CFG, MMA8451_RANGE_4_G, hi2c1);

    // Se establece la frecuencia de muestreo a 200Hz
    write_register(MMA8451_REG_CTRL_REG1, MMA8451_DATARATE_200_HZ, hi2c1);

    // Data ready interrupt en INT1
    write_register(MMA8451_REG_CTRL_REG4, 0x01, hi2c1);             // Activamos la interrupción
    wirte_register(MMA8451_REG_CTRL_REG5, 0x01, hi2c1);             // Se establece la interrupción en INT1
}
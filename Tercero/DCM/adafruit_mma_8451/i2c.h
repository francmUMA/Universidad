#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define MMA8451_DEFAULT_ADDRESS                                                \
  (0x1D) //!< Default MMA8451 I2C address, if A is GND, its 0x1C
/*=========================================================================*/

void write_register(uint8_t , uint16_t , I2C_HandleTypeDef);
uint8_t *read_register(uint8_t , I2C_HandleTypeDef);

#endif

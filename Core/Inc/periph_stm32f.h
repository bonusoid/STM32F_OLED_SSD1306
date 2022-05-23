/*
 * periph_stm32f.h
 *
 *  Created on: May 22, 2022
 *      Author: bonusoid
 */

#ifndef INC_PERIPH_STM32F_H_
#define INC_PERIPH_STM32F_H_

#include "main.h"

I2C_HandleTypeDef hi2c1;

void MX_I2C1_Init(void); //I2C initialization
void i2c_write_2byte(unsigned char devaddr, unsigned char dbyte1, unsigned char dbyte2);  //I2C send 2 bytes

#endif /* INC_PERIPH_STM32F_H_ */

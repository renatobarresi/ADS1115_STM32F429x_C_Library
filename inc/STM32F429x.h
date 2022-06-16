/*
 * ADS1115_STM32F429x.h
 *
 *  Created on: Jun 13, 2022
 *      Author: renato
 */

#ifndef STM32F429X_H_
#define STM32F429X_H_

#include <stdint.h>

/*
The ADS111x have one address pin, ADDR, that configures the I2C address of the device. This pin can be
connected to GND, VDD, SDA, or SCL, allowing for four different addresses to be selected with one pin
 */

void _ADS1115_delay(uint32_t delay);

uint8_t _ADS1115_I2C_init();
uint8_t _ADS1115_I2C_write(uint8_t address, uint8_t *pData, uint16_t size);
uint8_t _ADS1115_I2C_read(uint8_t address, uint8_t *pData, uint16_t size);
uint8_t _ADS1115_I2C_reg_write(uint16_t devAddr, uint16_t memAddr, uint8_t *pData, uint16_t size);
uint8_t _ADS1115_I2C_reg_read(uint16_t devAddr, uint16_t memAddr, uint8_t *pData, uint16_t size);
#endif /* ADS1115_STM32F429X_H_ */

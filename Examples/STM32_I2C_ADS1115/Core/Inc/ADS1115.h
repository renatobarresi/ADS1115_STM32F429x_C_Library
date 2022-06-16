/*
 * ADS1115.h
 *
 *  Created on: Jun 13, 2022
 *      Author: renato
 */

#ifndef ADS1115_H_
#define ADS1115_H_

#include <stdint.h>
#include "STM32F429x.h" //Hardware dependent functions

/*Device I2C address*/
#define ADS1115_I2C_ADDR_GND (0X48 << 1)
#define ADS1115_I2C_ADDR_VCC (0X49 << 1)
#define ADS1115_I2C_ADDR_SDA (0X4A << 1)
#define ADS1115_I2C_ADDR_SCL (0X4B << 1)

/*Device mode*/
#define ADS1115_CONT_MODE 0	  //continuous mode
#define ADS1115_SINGLE_SHOT 1 //single shot mode (default)

/*Device PGA mode*/
#define ADS1115_RANGE_6144 0 //+/- 6144 mV
#define ADS1115_RANGE_4096 1 //+/- 4096 mV
#define ADS1115_RANGE_2048 2 //+/- 2048 mV (default)
#define ADS1115_RANGE_1024 3 //+/- 1024 mV
#define ADS1115_RANGE_0512 4 //+/- 512 mV
#define ADS1115_RANGE_0256 5 //+/- 256 mV

/*Device Channel mode*/
#define ADS1115_COMP_0_GND 0
#define ADS1115_COMP_1_GND 1
#define ADS1115_COMP_2_GND 2
#define ADS1115_COMP_3_GND 3
#define ADS1115_COMP_0_1 4
#define ADS1115_COMP_0_3 5
#define ADS1115_COMP_1_3 6
#define ADS1115_COMP_2_3 7

/*Device handler*/
typedef struct _ADS1115_Handler{
	uint8_t address;		//ADS1115 Address
	uint8_t configReg[2]; 	//ADS1115 configuration register array -> [0] MSB, [1] LSB
	uint8_t conversionRegBuff[2];  //Conversion register buffer [0] MSB [1] LSB
	float FS;				//ADS1115 Full-Scale (FS) range
}ADS1115_handler;

/*Public functions*/
uint8_t ADS1115_init(ADS1115_handler *ads, uint8_t address);
uint8_t ADS1115_Set_Mode(ADS1115_handler *ads, uint8_t mode);
uint8_t ADS1115_Set_Volt_Range(ADS1115_handler *ads, uint8_t mode);
uint8_t ADS1115_Set_Compare_Channel(ADS1115_handler *ads, uint8_t channel);
uint8_t ADS1115_Start_Single_Measurement(ADS1115_handler *ads);
float ADS1115_Get_Volt(ADS1115_handler *ads);
#endif /* ADS1115_H_ */

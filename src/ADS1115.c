/*
 * ADS1115.c
 *
 *  Created on: Jun 13, 2022
 *      Author: renato
 */

#include "ADS1115.h"

/*******************Private global variables***************************/

/*Device memory address*/
static const uint8_t ADS1115RegConversion = 0x00;
static const uint8_t ADS1115RegConfig = 0x01;
static const uint8_t ADS1115RegLoThresh = 0x02;
static const uint8_t ADS1115RegHiThresh = 0x03;

/*Configuration register (half-word register) LSB and MSB*/
static uint8_t ADS1115DefRegConfigLSB =  0b10000011;
static uint8_t ADS1115DefRegConfigMSB =  0b00000101;

/**********************Private functions**********************/

static uint8_t _ADS1115_write_config_reg(ADS1115_handler *ads){
	uint8_t retVal;
	uint8_t tempBuff[2];
	tempBuff[1] = ads->configReg[1]; //LSB
	tempBuff[0] = ads->configReg[0]; //MSB

	retVal = _ADS1115_I2C_reg_write((uint16_t)ads->address, (uint16_t)ADS1115RegConfig, tempBuff, 2);
	return retVal;
}

static uint8_t _ADS1115_read_conversion_reg(ADS1115_handler *ads){
	uint8_t retVal;

	retVal = _ADS1115_I2C_reg_read((uint16_t)ads->address, (uint16_t)ADS1115RegConversion, ads->conversionRegBuff, 2);
	return retVal;
}

/**********************Public functions**********************/

/* @brief I2C peripheral initialization
 * @param ads: pointer to object handler of type ADS1115_handler
 * @param address: device I2C address
 * @retval 1: if I2C peripheral init was successful
 * @retval 0: if error while init I2C peripheral
 */
uint8_t ADS1115_init(ADS1115_handler *ads, uint8_t address){
	if(_ADS1115_I2C_init() == 0){
		return 0;
	}
	ads->address = address;
	ads->configReg[0] = ADS1115DefRegConfigMSB;
	ads->configReg[1] = ADS1115DefRegConfigLSB;
	ads->conversionRegBuff[0] = 0;
	ads->conversionRegBuff[1] = 0;
	ads->FS = 2.048;
	return 1;
}

/* @brief Set ADS1115 to either continuous or single shot conversion mode
 * @param ads: pointer to object handler of type ADS1115_handler
 * @param ADS1115_SINGLE_SHOT set to single shot
 * @param ADS1115_CONT_MODE set to continuous
 * @retval 1 communication was successful
 * @retval 0 error while communicating
 */
uint8_t ADS1115_Set_Mode(ADS1115_handler *ads, uint8_t mode){

	uint8_t retVal;

	/*the lsb of the register defines the mode, for single shot needs to be 1, for continuous mode 0*/
	if(mode == 1){ //single shot
		ads->configReg[0] |= (1<<0);
	}else{ //continuous mode
		ads->configReg[0] &= ~(1<<0);
	}
	/*Send Config register address*/
	retVal = _ADS1115_write_config_reg(ads);
	return retVal;

}

/* @brief Configures the Programmable Gain Amplifier
 * @param ads: pointer to object handler of type ADS1115_handler
 * @param mode: ADS1115_RANGE_6144 +-6.144 V
 * @param mode: ADS1115_RANGE_4096 +-4.096 V
 * @param mode: ADS1115_RANGE_2048 +-2.048 V
 * @param mode: ADS1115_RANGE_1024 +-1.024 V
 * @param mode: ADS1115_RANGE_0512 +-0.512 V
 * @param mode: ADS1115_RANGE_0256 +-0.256 V
 * @retval 1 communication was successful
 * @retval 0 error while communicating
 */
uint8_t ADS1115_Set_Volt_Range(ADS1115_handler *ads, uint8_t mode){
	switch(mode){
		case 0:
			ads->configReg[0] &= ~(1 << 1);
			ads->configReg[0] &= ~(1 << 2);
			ads->configReg[0] &= ~(1 << 3);
			ads->FS = 6.144;
			break;
		case 1:
			ads->configReg[0] |= (1 << 1);
			ads->configReg[0] &= ~(1 << 2);
			ads->configReg[0] &= ~(1 << 3);
			ads->FS = 4.096;
			break;
		case 2:
			ads->configReg[0] &= ~(1 << 1);
			ads->configReg[0] |= (1 << 2);
			ads->configReg[0] &= ~(1 << 3);
			ads->FS = 2.048;
			break;
		case 3:
			ads->configReg[0] |= (1 << 1);
			ads->configReg[0] |= (1 << 2);
			ads->configReg[0] &= ~(1 << 3);
			ads->FS = 1.024;
			break;
		case 4:
			ads->configReg[0] &= ~(1 << 1);
			ads->configReg[0] &= ~(1 << 2);
			ads->configReg[0] |= (1 << 3);
			ads->FS = 0.512;
			break;
		case 5:
			ads->configReg[0] |= (1 << 1);
			ads->configReg[0] &= ~(1 << 2);
			ads->configReg[0] |= (1 << 3);
			ads->FS = 0.256;
			break;
		default:
			ads->configReg[0] &= ~(1 << 1);
			ads->configReg[0] &= ~(1 << 2);
			ads->configReg[0] &= ~(1 << 3);
			ads->FS = 2.048;
			break;
	}
	uint8_t retVal;
	retVal = _ADS1115_write_config_reg(ads);
	return retVal;
}

/* @brief
 * @param ads: pointer to object handler of type ADS1115_handler
 * @param channel: ADC channel to measure
 * @retval 1: if communication was successful
 * @retval 0: if error while trying to communicate
 *
 * TODO: Implement register manipulation for differential measurement
 */

uint8_t ADS1115_Set_Compare_Channel(ADS1115_handler *ads, uint8_t channel){
	switch(channel){
		case 0:
			ads->configReg[0] &= ~(1 << 4);
			ads->configReg[0] &= ~(1 << 5);
			ads->configReg[0] |= (1 << 6);
			break;
		case 1:
			ads->configReg[0] |= (1 << 4);
			ads->configReg[0] &= ~(1 << 5);
			ads->configReg[0] |= (1 << 6);
			break;
		case 2:
			ads->configReg[0] &= ~(1 << 4);
			ads->configReg[0] |= (1 << 5);
			ads->configReg[0] |= (1 << 6);
			break;
		case 3:
			ads->configReg[0] |= (1 << 4);
			ads->configReg[0] |= (1 << 5);
			ads->configReg[0] |= (1 << 6);
			break;
	}
	uint8_t retVal;
	retVal = _ADS1115_write_config_reg(ads);
	return retVal;
}
/* @brief Make a single shot measurement
 * @param ads: pointer to object handler of type ADS1115_handler
 * @retval 1: if communication was successful
 * @retval 0: if error while communicating
 */
uint8_t ADS1115_Start_Single_Measurement(ADS1115_handler *ads){
	uint8_t retVal;

	/*The msb signals the ADC to begin doing a conversion*/
	ads->configReg[0] |= (1 << 7);
	retVal = _ADS1115_write_config_reg(ads);

	if(retVal == 0){
		return 0;
	}

	_ADS1115_delay(10);

	retVal = _ADS1115_read_conversion_reg(ads);

	return retVal;
}
/* @brief Calculates the voltage using the FS and the conversionRegBuff
 * @param ads: pointer to object handler of type ADS1115_handler
 * @retval Voltage
 */
float ADS1115_Get_Volt(ADS1115_handler *ads){
	float VPS = ads->FS/32768.0;
	uint32_t val;

	val = ads->conversionRegBuff[0] << 8 | ads->conversionRegBuff[1];
	if(val>32768) val = 0;
	return val*VPS;
}

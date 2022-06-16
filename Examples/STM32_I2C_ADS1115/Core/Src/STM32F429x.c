/*
 * STM32F42x.c
 *
 *  Created on: Jun 13, 2022
 *      Author: renato
 */

#include "STM32F429x.h"
#include "stm32f4xx_hal.h"

/**********************Static variables***********************/

I2C_HandleTypeDef hi2c1;

/********************Helper functions*****************/

void _ADS1115_delay(uint32_t delay){
	HAL_Delay(delay);
}


/********************Low Level I2C functions*****************/

/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();

  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }

}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

    /* I2C1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }

}

/********************High Level I2C functions*****************/

/* @brief STM32F429x I2C peripheral initialization
 * @param none
 * @retval none
 */
uint8_t _ADS1115_I2C_init(){
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		return 0;
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		return 0;
	}
	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		return 0;
	}

	return 1;
}

uint8_t _ADS1115_I2C_reg_write(uint16_t devAddr, uint16_t memAddr, uint8_t *pData, uint16_t size){
	HAL_StatusTypeDef retVal;

	retVal = HAL_I2C_Mem_Write(&hi2c1, devAddr, memAddr, sizeof(uint8_t), pData, 2, HAL_MAX_DELAY);
	if(retVal == HAL_ERROR){
		return 0;
	}else{
		retVal = 1;
	}
	return retVal;
}

uint8_t _ADS1115_I2C_reg_read(uint16_t devAddr, uint16_t memAddr, uint8_t *pData, uint16_t size){
	HAL_StatusTypeDef retVal;

	retVal = HAL_I2C_Mem_Read(&hi2c1, devAddr, memAddr, sizeof(uint8_t), pData, 2, HAL_MAX_DELAY);
	if(retVal == HAL_ERROR){
		return 0;
	}else{
		retVal = 1;
	}
	return retVal;
}


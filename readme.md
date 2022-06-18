# ADS1115 16-bit ADC C Library for the STM32F429x

Version 1.0

## Atributos
```
/*Device I2C address*/
ADS1115_I2C_ADDR_GND 
ADS1115_I2C_ADDR_VCC 
ADS1115_I2C_ADDR_SDA 
ADS1115_I2C_ADDR_SCL 

/*Device mode*/
ADS1115_CONT_MODE 
ADS1115_SINGLE_SHOT 

/*Device PGA mode*/
ADS1115_RANGE_6144 
ADS1115_RANGE_4096 
ADS1115_RANGE_2048 
ADS1115_RANGE_1024 
ADS1115_RANGE_0512 
ADS1115_RANGE_0256 

/*Device Channel mode*/
ADS1115_COMP_0_GND 
ADS1115_COMP_1_GND 
ADS1115_COMP_2_GND 
ADS1115_COMP_3_GND 
ADS1115_COMP_0_1 
ADS1115_COMP_0_3
ADS1115_COMP_1_3 
ADS1115_COMP_2_3 

/*Device handler*/
typedef struct _ADS1115_Handler{
	uint8_t address;		//ADS1115 Address
	uint8_t configReg[2]; 	//ADS1115 configuration register array -> [0] MSB, [1] LSB
	uint8_t conversionRegBuff[2];  //Conversion register buffer -> [0] MSB [1] LSB
	float FS;				//ADS1115 Full-Scale (FS) range
}ADS1115_handler;
```

## Metodos
```
uint8_t ADS1115_init(ADS1115_handler *ads, uint8_t address);
uint8_t ADS1115_Set_Mode(ADS1115_handler *ads, uint8_t mode);
uint8_t ADS1115_Set_Volt_Range(ADS1115_handler *ads, uint8_t mode);
uint8_t ADS1115_Set_Compare_Channel(ADS1115_handler *ads, uint8_t channel);
uint8_t ADS1115_Start_Single_Measurement(ADS1115_handler *ads);
float ADS1115_Get_Volt(ADS1115_handler *ads);
```

## Directory

* inc/ADS1115.h High level API header file for the ADS1115
* src/ADS1115.c API implementation

* inc/STM32F429x.h "Low level" API  Port header file for the ADS1115.h
* src/STM32F429x.c API implementation

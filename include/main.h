#ifndef __MAIN_H
#define __MAIN_H

#include <stm32f0xx.h>
#include <stm32f0xx_hal.h>
#include <stdio.h>

#define LPS331AP_ADDRESS 0xBA // I2C address of LPS331AP sensor
#define TEMP_OUT_L_REG 0x2B  // register address for temperature data (LSB)
#define TEMP_OUT_H_REG 0x2C  // register address for temperature data (MSB)

extern UART_HandleTypeDef huart5;
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;

void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void I2C_Init();
void ADC_Init();
uint16_t ADC_Read();
void LPS331AP_Init(void);
float LPS331AP_ReadTemperature(void);

#endif /* __MAIN_H */

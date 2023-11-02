#include "i2c.h"

void I2C_Init() {
    // Initialize and configure GPIO pins for I2C
    __HAL_RCC_GPIOB_CLK_ENABLE(); // Enable GPIOB clock
    __HAL_RCC_I2C1_CLK_ENABLE();  // Enable I2C1 clock

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; // I2C pins in Open-Drain mode
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_I2C1; // I2C1 is on AF1

    // Initialize SCL pin (PB8)
    GPIO_InitStruct.Pin = I2C_SCL_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Initialize SDA pin (PB9)
    GPIO_InitStruct.Pin = I2C_SDA_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // I2C Configuration
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x00A51314;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0xFF;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c1);
}

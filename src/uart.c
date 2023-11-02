#include "uart.h"

void UART_Init() {
    // UART Configuration
    huart5.Instance = USART5;
    huart5.Init.BaudRate = 9600;
    huart5.Init.WordLength = UART_WORDLENGTH_8B;
    huart5.Init.StopBits = UART_STOPBITS_1;
    huart5.Init.Parity = UART_PARITY_NONE;
    huart5.Init.Mode = UART_MODE_TX_RX;
    huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    HAL_UART_Init(&huart5);
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
    // Enable peripheral clock for UART5
    __HAL_RCC_USART5_CLK_ENABLE();

    // Enable GPIO Port B clock
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configure UART5 TX and RX pins
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART5;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void UART_SendData(const char* data) {
    HAL_UART_Transmit(&huart5, (uint8_t*)data, strlen(data), HAL_MAX_DELAY);
}

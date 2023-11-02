#include "ADC.h"

void ADC_Init() {
    // ADC Configuration
    __HAL_RCC_ADC1_CLK_ENABLE(); // Enable ADC clock
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable GPIO clock

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_4; // PA4 for your analog input (e.g., soil moisture)
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // analog input
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    hadc1.Instance = ADC1; // ADC instance
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; // Clock divider
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; // 12-bit resolution
    hadc1.Init.ScanConvMode = DISABLE; // Disable scan mode
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT; // Data alignment
    hadc1.Init.ContinuousConvMode = DISABLE; // Single conversion mode
    hadc1.Init.DiscontinuousConvMode = DISABLE; // Disable discontinuous mode
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START; // Trigger for conversion
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.Overrun = OVR_DATA_OVERWRITTEN;
    hadc1.Init.SamplingTimeCommon = ADC_SAMPLETIME_13CYCLES_5; // Common sampling time

    HAL_ADC_Init(&hadc1);

    // ADC-Channel Configuration for channel 4 (analog input)
    ADC_ChannelConfTypeDef sConfigChannel4;
    sConfigChannel4.Channel = ADC_CHANNEL_4;
    sConfigChannel4.Rank = ADC_RANK_CHANNEL_NUMBER;
    sConfigChannel4.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;

    HAL_ADC_ConfigChannel(&hadc1, &sConfigChannel4);
}

// Read the ADC Value
uint16_t ADC_Read() {
    // Start the ADC conversion
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint16_t adc_value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return adc_value;
}

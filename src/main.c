#include "main.h"
#include "UART.h"
#include "I2C.h"
#include "ADC.h"
#include "LPS331AP.h"

int main() {
    // Initialize the HAL
    HAL_Init();

    // Initialize the ADC
    ADC_Init();

    // Initialize UART
    UART_Init();
    HAL_UART_MspInit(&huart5);
    I2C_Init();
    // Initialize the LPS331AP sensor
    LPS331AP_Init();
    // Thresholds for soil moisture
    uint16_t SchwellenwertNass = 2360; // very wet, switch off early, so that the pump switches off in time
    uint16_t SchwellenwertTrocken = 2500; // dry

    while (1) {
        // Read the ADC value
        volatile uint16_t adc_value = ADC_Read();

        //asm volatile ("bkpt #03");

        // Read the temperature from the sensor
        float temperature = LPS331AP_ReadTemperature();

        // Send ADC value via UART
        char adc_message[50];
        snprintf(adc_message, sizeof(adc_message), "adc:%d\n", adc_value);
        UART_SendData(adc_message);

        // Send temperature data via UART
        char temp_message[50];
        snprintf(temp_message, sizeof(temp_message), "Temperature: %.2fC\n", temperature);
        UART_SendData(temp_message);

        // Check the ADC value and control USB power
        if (adc_value >= SchwellenwertTrocken) {
            // Turn on USB power since the plant is too dry
            UART_SendData("usb_on");
        } else if (adc_value <= SchwellenwertNass) {
            // Turn off USB power since the plant might get too wet
            UART_SendData("usb_off");
        }

        HAL_Delay(1000); // delay between ADC readings
    }

    return 0;
}


#include "LPS331AP.h"


void LPS331AP_Init(void) {
    uint8_t ctrl_reg1_data = 0x90; // Set ODR to 25 Hz and enable the sensor in normal mode
  HAL_I2C_Mem_Write(&hi2c1, LPS331AP_ADDRESS, 0x20, 1, &ctrl_reg1_data, 1, 1000); // Write to CTRL_REG1
}

float LPS331AP_ReadTemperature(void) {
uint8_t temp_out_l_data = 0;
  uint8_t temp_out_h_data = 0;
  int16_t temp_out_data = 0;
  float temperature = 0.0;
  
  HAL_I2C_Mem_Read(&hi2c1, LPS331AP_ADDRESS, 0x2B, 1, &temp_out_l_data, 1, 1000); // Read TEMP_OUT_L
  HAL_I2C_Mem_Read(&hi2c1, LPS331AP_ADDRESS, 0x2C, 1, &temp_out_h_data, 1, 1000); // Read TEMP_OUT_H
  
  temp_out_data = (temp_out_h_data << 8) | temp_out_l_data; // Combine the two bytes into a signed 16-bit integer
  temperature = (float)temp_out_data / 480.0 + 42.5; // Convert the raw temperature data to degrees Celsius
  
  return temperature;
}


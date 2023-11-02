# Plant-Bot-RPI

This project realises a Plant-Bot using the Raspberry Pi 3b+ equipped with an analogue capacitive soil moisture sensor and a water pump to measure soil moisture and determine whether the plant needs water. 
If necessary, the plant will be watered using the pump. Once the soil reaches an adequate moisture level, as indicated by the soil moisture sensor, the pump will automatically turn off. The output on the Raspberry Pi contains additional information such as the current soil moisture level, the pump status (on or off), and the temperature in degrees Celsius.

## Project Setup
The water pump is connected to a Raspberry Pi via USB and placed in a container filled with water. A hose is used to connect the pump to the plant pot. The soil moisture sensor is inserted into the soil and connected to the Raspberry Pi via ADC.

### Soil Moisture Sensor Normalization
The soil moisture sensor provides an output voltage in the range of 0-3V. The range depends on the selected ADC resolution. With 12 bit resolution the range is 0 to 4095. A higher value indicates dry soil and a lower value indicates higher moisture content. To control the water pump effectively, we use a hysteresis mechanism that shuts it off slightly earlier to ensure the plant has time to absorb the water without being overwatered.

### Controlling the Water Pump via uhubctl
The water pump  starts running as soon as it is connected to a USB port and stops when the power supply is interrupted. To address this, we used the [uhubctl](https://github.com/mvp/uhubctl) library  to control the USB ports on the software side. This ensures that the pump is only activated when the soil moisture sensor provides the appropriate readings.

## Software Components
### Separation of Components
To separate the components, we divided the functionality between a Python script and an STM32F0-based program. Functions related to the Raspberry Pi are collected in the Python script, including controlling the USB power. We use an additional Bash script to handle the USB power control. This ensures that calling the uhubctl library in the Python program does not require sudo permissions.

### Communication between STM32F0 and Raspberry Pi via UART
The main program reads the ADC value and, depending on the value, sends "usb-off" if the soil is too moist or "usb-on" if the soil is too dry via UART. The Python program on the Raspberry Pi receives these commands and controls the USB power accordingly, stopping the pump when the plant is sufficiently moist. To avoid toggling the USB ports if they are already turned on, we introduced an "usb_power_state" variable to track the current state.

### Additional Features
The project provides additional information such as current soil moisture, pump status (on or off) and temperature in degrees Celsius. The Python script integrates this functionality to display all the critical data directly on the Raspberry Pi. The pump status is easy to determine from the "usb_power_state" variable: if it's set to 1, the pump is on (via "usb_on"), otherwise it's off (via "usb_off"). To measure the temperature, we read out the temperature value of the LPS331AP barometer on the extension board via I2C. This value is then converted into degrees Celsius. Both the ADC value and the temperature are read in the main program, sent to the Raspberry Pi via UART and displayed there.

import os
import RPi.GPIO as GPIO
import time
import serial

GPIO.setmode(GPIO.BOARD)
GPIO.setup(18, GPIO.IN)
usb_power_state = True  # Initially, USB power is on
script_execution_status = 0

# Function to control USB power using the Bash script
def control_usb_power(enable):
    global script_execution_status
    global usb_power_state  # Track the current USB power state

    if enable and not usb_power_state:
        command = "./usb_control.sh on"
        print(f"Turning USB power on: {command}")
        result = os.system(command)

        if result == 0:
            script_execution_status = 1
            usb_power_state = True
            print("USB power turned on successfully")
        else:
            script_execution_status = -1
            print("Failed to turn on USB power")
    elif not enable and usb_power_state:
        command = "./usb_control.sh off"
        print(f"Turning USB power off: {command}")
        result = os.system(command)

        if result == 0:
            script_execution_status = 1
            usb_power_state = False
            print("USB power turned off successfully")
        else:
            script_execution_status = -1
            print("Failed to turn off USB power")

if __name__ == "__main__":
    ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)

    try:
        # Initialize USB power to be on
        control_usb_power(True)

        while True:
            # Read data from UART
            data = ser.readline().decode().strip()

            # Check if the received data includes "adc:" (indicating an ADC value)
            if "adc:" in data:
                adc_value = int(data.split(":")[1])
                # Print the received ADC value
                print(f"Received ADC Value: {adc_value}")

            # Check if the received data includes "Temperature:"
            if "Temperature:" in data:
                temperature = float(data.split(":")[1].strip("C"))
                # Print the received temperature
                print(f"Received Temperature: {temperature}C")

            # Print the pump status
            print(f"Pump Status: {'usb_on' if usb_power_state else 'usb_off'}")

            if data == "usb_on":
                control_usb_power(True)
            elif data == "usb_off":
                control_usb_power(False)

    except KeyboardInterrupt:
        # Handle Ctrl + C interruption
        print("Program interrupted by the user.")

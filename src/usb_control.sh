#!/bin/bash

HUB="1-1"
PORT="2"

# Bash-Skript zum Ein- und Ausschalten der USB-Stromversorgung

if [ "$1" == "on" ]; then
    sudo uhubctl -l "$HUB" -p "$PORT" -a 1 # USB-Stromversorgung einschalten
elif [ "$1" == "off" ]; then
    sudo uhubctl -l "$HUB" -p "$PORT" -a 0 # USB-Stromversorgung ausschalten
else
    echo "Ungültiges Argument. Verwenden Sie 'on' oder 'off'."
fi


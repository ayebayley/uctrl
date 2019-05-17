#!/bin/bash
# Compile and upload a C program to the ATMega328 microcontroller

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c main.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c TWI_Master.c
avr-gcc -mmcu=atmega328p main.o TWI_Master.o -o main
avr-objcopy -O ihex -R .eeprom main main.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex

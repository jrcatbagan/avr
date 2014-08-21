# File: makefile
# Author: Jarielle Catbagan
# Created: 24, April 2014

build: uart.o
	avr-gcc -mmcu=atmega328p -o uart.elf uart.o
	avr-objcopy -j .text -j .data -O ihex uart.elf uart.hex
uart.o: uart.c
	avr-gcc -Os -mmcu=atmega328p -c uart.c
program: uart.hex
	avrdude -p atmega328p -P usb -c usbtiny -U flash:w:uart.hex
clean:
	rm -f uart.o
	rm -f uart.elf
	rm -f uart.hex

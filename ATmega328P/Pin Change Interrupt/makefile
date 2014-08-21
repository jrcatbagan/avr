# File: makefile
# Author: Jarielle Catbagan
# Created: 17, March 2014

build: pc-interrupt.o
	avr-gcc -mmcu=atmega328p -o pc-interrupt.elf pc-interrupt.o
	avr-objcopy -j .text -j .data -O ihex pc-interrupt.elf pc-interrupt.hex
pc-interrupt.o: pc-interrupt.c
	avr-gcc -Os -mmcu=atmega328p -c pc-interrupt.c
program: pc-interrupt.hex
	avrdude -p atmega328p -P usb -c usbtiny -U flash:w:pc-interrupt.hex
clean:
	rm -f pc-interrupt.o
	rm -f pc-interrupt.elf
	rm -f pc-interrupt.hex

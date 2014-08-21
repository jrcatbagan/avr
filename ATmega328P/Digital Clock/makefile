# File: makefile
# Author: Jarielle Catbagan
# Created: 02, April 2014

build: digital-clock.o lcd-char.o
	avr-gcc -mmcu=atmega328p -o digital-clock.elf digital-clock.o lcd-char.o
	avr-objcopy -j .text -j .data -O ihex digital-clock.elf digital-clock.hex
digital-clock.o: digital-clock.c
	avr-gcc -Os -mmcu=atmega328p -c digital-clock.c
lcd-char.o: lcd-char.c
	avr-gcc -Os -mmcu=atmega328p -c lcd-char.c
program: digital-clock.hex
	avrdude -p atmega328p -P usb -c usbtiny -U flash:w:digital-clock.hex
clean:
	rm -f digital-clock.o
	rm -f lcd-char.o
	rm -f digital-clock.elf
	rm -f digital-clock.hex

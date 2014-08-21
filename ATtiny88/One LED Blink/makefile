# File: makefile
# Author: Jarielle Catbagan
# Created: 04, April 2014

build: led-blink.o
	avr-gcc -mmcu=attiny88 -o led-blink.elf led-blink.o
	avr-objcopy -j .text -j .data -O ihex led-blink.elf led-blink.hex
led-blink.o: led-blink.c
	avr-gcc -Os -mmcu=attiny88 -c led-blink.c
program: led-blink.hex
	avrdude -p attiny88 -P usb -c usbtiny -U flash:w:led-blink.hex
clean:
	rm -f led-blink.o
	rm -f led-blink.elf
	rm -f led-blink.hex

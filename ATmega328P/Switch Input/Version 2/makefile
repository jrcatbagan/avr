
build: switch-input.o
	avr-gcc -mmcu=atmega328p -o switch-input.elf switch-input.o
	avr-objcopy -j .text -j .data -O ihex switch-input.elf switch-input.hex
switch-input.o: switch-input.c
	avr-gcc -Os -mmcu=atmega328p -c switch-input.c
program: switch-input.hex
	avrdude -p atmega328p -P usb -c usbtiny -U flash:w:switch-input.hex
clean:
	rm -f switch-input.o
	rm -f switch-input.elf
	rm -f switch-input.hex

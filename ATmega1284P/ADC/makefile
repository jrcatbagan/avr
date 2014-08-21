
build: led-dim.o
	avr-gcc -mmcu=atmega1284p -o led-dim.elf led-dim.o
	avr-objcopy -j .text -j .data -O ihex led-dim.elf led-dim.hex
led-dim.o: led-dim.c
	avr-gcc -Os -mmcu=atmega1284p -c led-dim.c
program: led-dim.hex
	avrdude -p atmega1284p -P usb -c usbtiny -U flash:w:led-dim.hex
clean:
	rm -f led-dim.o
	rm -f led-dim.elf
	rm -f led-dim.hex

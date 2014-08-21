
build: main.o
	avr-gcc -mmcu=attiny88 -o main.elf main.o
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
main.o: main.c
	avr-gcc -Os -mmcu=attiny88 -c main.c
program: main.hex
	avrdude -p attiny88 -P usb -c usbtiny -U flash:w:main.hex
clean:
	rm -f main.o
	rm -f main.elf
	rm -f main.hex

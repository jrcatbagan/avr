build: main.o
	avr-objcopy -O ihex main.o main.hex
main.o: main.S
	avr-as -mmcu=atmega1284p -o main.o main.S
program: main.hex
	avrdude -p atmega1284p -P usb -c usbtiny -U flash:w:main.hex
clean:
	rm -f main.o main.hex

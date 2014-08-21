build: pwm.o
	avr-gcc -mmcu=atmega328p -o pwm.elf pwm.o
	avr-objcopy -j .text -j .data -O ihex pwm.elf pwm.hex
pwm.o: pwm.c
	avr-gcc -Os -mmcu=atmega328p -c pwm.c
program: pwm.hex
	avrdude -p atmega328p -P usb -c usbtiny -U flash:w:pwm.hex
clean:
	rm -f pwm.o
	rm -f pwm.elf
	rm -f pwm.hex

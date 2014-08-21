// File: led-blink.c
// Created: 04, April 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* Flashes an LED with the Atmel AVR ATtiny88 */

// Code:

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void) {
        DDRB |= 1 << PINB0;
        DDRB &= ~(1 << PINB1);
        PORTB &= ~(1 << PINB0);
        PORTB |= 1 << PINB1;

        while(1) {
                if(bit_is_clear(PINB, 1))
                        PORTB |= 1 << PINB0;
                else
                        PORTB &= ~(1 << PINB0);
        }
        return 0;
}

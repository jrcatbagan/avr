// File: main.c
// Created: 02, April 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

#include <avr/io.h>
#define F_CPU 20000000UL
#include <util/delay.h>


int main(void) {
        DDRB |= 1 << PINB1;
        PORTB &= ~(1 << PINB1);
        
        while(1) {
                PORTB ^= (1 << PINB1);
                _delay_ms(1000);
        }
        return 0;
}

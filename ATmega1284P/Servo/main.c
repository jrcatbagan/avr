// File: main.c
// Created: 26, February 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void) {
        DDRB |= 1 << PINB0;
        PORTB &= ~(1 << PINB0);

        while(1) {
                PORTB |= 1 << PINB0;
                _delay_us(2000);
                PORTB &= ~(1 << PINB0);
                _delay_us(18000);
        }
}

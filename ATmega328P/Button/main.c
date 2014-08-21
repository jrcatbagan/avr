// FIle: main.c
// Created: 13, April 2014

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
        DDRD &= ~(1 << PIND6 | 1 << PIND7);
        PORTD |= (1 << PIND6 | 1 << PIND7);
        DDRC |= (1 << PINC0 | 1 << PINC1 | 1 << PINC2 | 1 << PINC3);
        PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 | 1 << PINC3);
        while(1) {
                if(bit_is_clear(PIND, 6) && bit_is_clear(PIND, 7)) {
                        PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 | 1 << PINC3);
                }
                else if(bit_is_clear(PIND, 6) && bit_is_set(PIND, 7)) {
                        PORTC &= ~(1 << PINC2 | 1 << PINC3);
                        PORTC |= 1 << PINC1;
                        while(bit_is_clear(PIND, 6) && bit_is_set(PIND, 7)) {
                                PORTC &= ~(1 << PINC0);
                                _delay_us(25);
                                PORTC |= 1 << PINC0;
                                _delay_us(75);
                        }
                        PORTC &= ~(1 << PINC1);
                }
                else if(bit_is_set(PIND, 6) && bit_is_clear(PIND, 7)) {
                        PORTC &= ~(1 << PINC0 | 1 << PINC1);
                        PORTC |= 1 << PINC3;
                        while(bit_is_set(PIND, 6) && bit_is_clear(PIND, 7)) {
                                PORTC &= ~(1 << PINC2);
                                _delay_us(25);
                                PORTC |= 1 << PINC2;
                                _delay_us(75);
                        }
                        PORTC &= ~(1 << PINC3);
                }
                else {
                        PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 | 1 << PINC3);
                }
        }
        return 0;
}

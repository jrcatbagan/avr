// File: main.c
// Created: 16, January 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
        DDRB |= 1 << PINB0;
        PORTB &= ~(1 << PINB0);
        TCNT1 = 0;
        ICR1 = 31249;
        TIMSK1 |= (1 << OCIE1A);
        sei();
        TCCR1B |= ((1 << WGM13) | (1 << WGM12) | (1 << CS12));
        
        while(1) {
                ;
        }
        return 0;
} 

ISR(TIMER1_COMPA_vect) {
        PORTB ^= 1 << PINB0;
}


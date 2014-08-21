// File: pc-interrupt.c
// Created: 17, March 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* toggles an LED based on a switch input on a pin configured to see the
   change in logic level (pin-change interrupt) */

// Code:

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

uint8_t threshold = 0;

int main(void) {
        DDRC |= 1 << PINC0;
        PORTC &= ~(1 << PINC0);
        
        PCICR |= 1 << PCIE0;
        PCMSK0 |= 1 << PCINT0;
        sei();
        
        
        while(1) {
                ;
        }
        return 0;
}

ISR(PCINT0_vect) {
        if(threshold == 0) {
                PORTC ^= 1 << PINC0;
                ++threshold;
        }
        else {
                threshold = 0;
        }
}

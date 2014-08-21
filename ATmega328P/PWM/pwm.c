// FIle: pwm.c
// Created: 28, February 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void) {
        uint16_t time1, time2, i;
        DDRB |= 1 << PINB0;
        PORTB &= ~(1 << PINB0);
        while(1) {
                for(time1 = 0, time2 = 100; time2 > 0; ++time1, --time2) {
                        for(i = 0; i < 10; ++i) {
                                PORTB |= 1 << PINB0;
                                _delay_us(time1);
                                PORTB &= ~(1 << PINB0);
                                _delay_us(time2);
                        }
                }
        }
}

// File: led-dim.c
// Created: 03, February 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

// Code:

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void) {
        unsigned char temp, value;
        
        DDRD |= 1 << PIND5;
        DDRA &= ~(1 << PINA0);
        ADMUX |= ((1 << ADLAR));
        ADCSRA |= ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS1));
        DIDR0 |= (1 << ADC0D);
        /*
        TCCR1A |= ((1 << COM1A1) | (1 << COM1A0) | (1 << WGM11));
        TCCR1B |= ((1 << WGM13) | (1 << WGM12) | (1 << CS12));
        ICR1 = 62499;*/

        PORTD &= ~(1 << PIND5);
        
        while(1) {
                ADCSRA |= 1 << ADSC;
                do {
                        temp = ADCSRA;
                        temp &= (1 << ADIF);
                } while(temp == 0x00);
                ADCSRA |= 1 << ADIF;

                value = ADCH;
                if(value > 250 && value < 255) {
                        PORTD ^= 1 << PIND5;
                        _delay_ms(1000);
                }
                else if(value > 200 && value < 249) {
                        PORTD ^= 1 << PIND5;
                        _delay_ms(750);
                }
                else if(value > 150 && value < 199) {
                        PORTD ^= 1 << PIND5;
                        _delay_ms(500);
                }
                else if(value > 100 && value < 149) {
                        PORTD ^= 1 << PIND5;
                        _delay_ms(250);
                }
                else if(value > 50 && value < 99) {
                        PORTD ^= 1 << PIND5;
                        _delay_ms(100);
                }
                else {
                        PORTD = 0b00100000;
                }
        }
        return 0;
}

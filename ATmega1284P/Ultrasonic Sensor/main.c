// File: main.c
// Created: 25, February 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <inttypes.h>

#define USNSR_DDR DDRD
#define USNSR_PORT PORTD
#define USNSR_TRIGGER PIND5
#define USNSR_ECHO PIND6

volatile enum {END = 0, START} capture_state;
volatile uint16_t start_time, end_time;

int main(void) {
        uint16_t distance;
        USNSR_DDR |= 1 << USNSR_TRIGGER;
        USNSR_DDR &= ~(1 << USNSR_ECHO);
        USNSR_PORT &= ~(1 << USNSR_TRIGGER);

        DDRB |= 1 << PINB0;
        PORTB &= ~(1 << PINB0);

        TCCR1B |= 1 << ICNC1;
        sei();
        while(1) {
                start_time = 0;
                end_time = 0;
                capture_state = START;
                TIFR1 |= 1 << ICR1;
                TCNT1 = 0;
                TCCR1B |= 1 << ICES1;
                TCCR1B |= ((1 << CS10) | (1 << CS11));
                TIMSK1 |= 1 << ICIE1;
                USNSR_PORT |= 1 << USNSR_TRIGGER;
                _delay_us(10);
                USNSR_PORT &= ~(1 << USNSR_TRIGGER);
                _delay_ms(40);
                TIMSK1 &= ~(1 << ICIE1);
                TCCR1B &= ~((1 << CS10) | (1 << CS11));

                if(start_time < end_time) {
                        distance = ((end_time - start_time) * 4) / 148;
                        if(distance < 12) {
                                PORTB |= 1 << PINB0;
                        }
                        else {
                                PORTB &= ~(1 << PINB0);
                        }
                }
        }
        return 0;
}

ISR(TIMER1_CAPT_vect) {
        if(capture_state == START) {
                start_time = ICR1;
                TCCR1B &= ~(1 << ICES1);
                capture_state = END;
        }
        else {
                TIMSK1 &= ~(1 << ICIE1);
                end_time = ICR1;
        }
}

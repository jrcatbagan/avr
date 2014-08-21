// File: switch-input.c
// Created: 19, March 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

// Code:

#include <avr/io.h>
#include <inttypes.h>

#define D0A_SET bit_is_clear(PINC, 0)
#define D1A_SET bit_is_clear(PINC, 1)
#define D2A_SET bit_is_clear(PINC, 2)
#define D3A_SET bit_is_clear(PINC, 3)
#define D0B_SET bit_is_clear(PINC, 4)
#define D1B_SET bit_is_clear(PINC, 5)
#define D2B_SET bit_is_clear(PINB, 1)
#define D3B_SET bit_is_clear(PINB, 2)

int main(void) {
        uint8_t prev_dataline_val = 0, current_dataline_val = 0;
        
        DDRC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 | 1 << PINC3 | 1 << PINC4 |
                  1 << PINC5);
        DDRB &= ~(1 << PINB1 | 1 << PINB2);
        PORTC |= (1 << PINC0 | 1 << PINC1 | 1 << PINC2 | 1 << PINC3 | 1 << PINC4 |
                  1 << PINC5);
        PORTB |= (1 << PINB1 | 1 << PINB2);
        DDRD = 0xFF;
        PORTD = 0x00;
        while(1) {
                if(D0A_SET)
                        current_dataline_val |= 1 << 0;
                else
                        current_dataline_val &= ~(1 << 0);
                if(D1A_SET)
                        current_dataline_val |= 1 << 1;
                else
                        current_dataline_val &= ~(1 << 1);
                if(D2A_SET)
                        current_dataline_val |= 1 << 2;
                else
                        current_dataline_val &= ~(1 << 2);
                if(D3A_SET)
                        current_dataline_val |= 1 << 3;
                else
                        current_dataline_val &= ~(1 << 3);
                if(D0B_SET)
                        current_dataline_val |= 1 << 4;
                else
                        current_dataline_val &= ~(1 << 4);
                if(D1B_SET)
                        current_dataline_val |= 1 << 5;
                else
                        current_dataline_val &= ~(1 << 5);
                if(D2B_SET)
                        current_dataline_val |= 1 << 6;
                else
                        current_dataline_val &= ~(1 << 6);
                if(D3B_SET)
                        current_dataline_val |= 1 << 7;
                else
                        current_dataline_val &= ~(1 << 7);

                if(current_dataline_val != prev_dataline_val) {
                        PORTD = current_dataline_val;
                        prev_dataline_val = current_dataline_val;
                }
        }
        return 0;
}

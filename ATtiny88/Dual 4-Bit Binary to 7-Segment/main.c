// File: main.c
// Created: 06, April 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* Drives a 7-segment display based on a 4-bit binary input.  Can drive up to two digits
   where each digit is dictated by a separate 4-bit binary value */

// Code:

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <inttypes.h>

#define INPUT_DDR DDRD
#define INPUT_PORT PORTD
#define SR_DDR DDRC
#define SR_PORT PORTC
#define SR_DATA PINC0
#define SR_LATCH PINC1
#define SR_CLOCK PINC2
#define SR_CLEAR PINC3

#define D0A_SET bit_is_set(PIND, 0)
#define D1A_SET bit_is_set(PIND, 1)
#define D2A_SET bit_is_set(PIND, 2)
#define D3A_SET bit_is_set(PIND, 3)
#define D0B_SET bit_is_set(PIND, 4)
#define D1B_SET bit_is_set(PIND, 5)
#define D2B_SET bit_is_set(PIND, 6)
#define D3B_SET bit_is_set(PIND, 7)

void sr_clear(void);
void sr_shift8bit(uint8_t data);
void sr_latch(void);

uint8_t _7segment_bitmap[16] = {0X7E, 0x30, 0x6D, 0X79, 0X33, 0X5B, 0X5F, 0X70,
                                0X7F, 0X73, 0X77, 0X1F, 0X4E, 0X3D, 0X4F, 0x47};

int main(void) {
        uint8_t prev_dataline_val = 0xFF, current_dataline_val = 0;
        uint8_t value1, value2;
        
        INPUT_DDR = 0;
        SR_DDR |= (1 << SR_DATA | 1 << SR_LATCH | 1 << SR_CLOCK | 1 << SR_CLEAR);
        SR_PORT &= ~(1 << SR_DATA | 1 << SR_LATCH | 1 << SR_CLOCK);
        SR_PORT |= 1 << SR_CLEAR;

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
                        value1 = current_dataline_val;
                        value1 &= 0x0F;
                        value2 = current_dataline_val;
                        value2 &= 0xF0;
                        value2 = value2 >> 4;
                        prev_dataline_val = current_dataline_val;
                        sr_clear();
                        sr_shift8bit(_7segment_bitmap[value1]);
                        sr_shift8bit(_7segment_bitmap[value2]);
                        sr_latch();
                }
        }
        return 0;
}

void sr_clear() {
        SR_PORT &= ~(1 << SR_CLEAR);
        SR_PORT |= 1 << SR_CLEAR;
}

void sr_shift8bit(uint8_t data) {
        uint8_t i, bitmask = 0x01, temp;
        for(i = 0; i < 7; ++i) {
                temp = data;
                temp &= bitmask;
                if(temp == bitmask) {
                        SR_PORT |= 1 << SR_DATA;
                        SR_PORT |= 1 << SR_CLOCK;
                        SR_PORT &= ~(1 << SR_CLOCK);
                        SR_PORT &= ~(1 << SR_DATA);
                }
                else {
                        SR_PORT &= ~(1 << SR_DATA);
                        SR_PORT |= 1 << SR_CLOCK;
                        SR_PORT &= ~(1 << SR_CLOCK);
                }
                bitmask = bitmask << 1;
        }
}

void sr_latch() {
        SR_PORT |= 1 << SR_LATCH;
        SR_PORT &= ~(1 << SR_LATCH);
}

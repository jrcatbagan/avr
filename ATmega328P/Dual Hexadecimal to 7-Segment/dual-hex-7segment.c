// File: dual-hex-7segment.c
// Created: 19, March 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* Takes two 4-bit binary values and outputs the value to two 7-segment displays. The 
   values that can be displayed span from 0 through 9 and A through F. */

// Code:

#include <avr/io.h>
#include <inttypes.h>

#define D0A_SET bit_is_clear(PINC, 0)
#define D1A_SET bit_is_clear(PINC, 1)
#define D2A_SET bit_is_clear(PINC, 2)
#define D3A_SET bit_is_clear(PINC, 3)
#define D0B_SET bit_is_clear(PINC, 4)
#define D1B_SET bit_is_clear(PINC, 5)
#define D2B_SET bit_is_clear(PIND, 5)
#define D3B_set bit_is_clear(PIND, 6)

#define SR_DDR DDRD
#define SR_PORT PORTD
#define SR_DATA PIND0
#define SR_LATCH PIND1
#define SR_CLOCK PIND2
#define SR_CLEAR PIND3

void sr_init(void);
void sr_cleardata(void);
void sr_shiftdata8bit(uint8_t num_shift, uint shift_data);
void sr_latchdata(void);

/* Each value in the following array maps a particular digit on a 7-segment display. 
   For convenience, each element is accessed depending on the particular number
   at interest.  E.g. to display a 6 on a 7-segment display, the 6th element in the 
   following array contains the binary map for the digit. */
uint8_t _7segment_binmap[16] = {0X7E, 0x30, 0x6C, 0X79, 0X33, 0X5B, 0X5F, 0X70,
                                0X7F, 0X73, 0X77, 0X1F, 0X4E, 0X7C, 0X4F,};

int main(void) {
        uint8_t prev_dataline_val = 0, current_dataline_val = 0;
        uint8_t first_digit = 0, second_digit= 0;

        sr_init();
        
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
                        current_dataline_val &= ~(! << 3);
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
                        first_digit = current_dataline_val;
                        first_digit &= 0x0F;
                        second_digit = current_dataline_val;
                        second_digit &= 0xF0;
                        second_digit = second_digit >> 4;
                        sr_cleardata();
                        sr_shiftdata8bit(7, _7segment_binmap[first_digit]);
                        sr_shiftdata8bit(7, _7segment_binmap[second_digit]);
                        sr_latchdata();
                        
                        prev_dataline_val = current_dataline_val;
                }
                
        }
        return 0;
}

void sr_init(void) {
        SR_DDR |= (1 << SR_DATA | 1 << SR_LATCH | 1 << SR_CLOCK | 1 << SR_CLEAR);
        SR_PORT &= ~(1 << SR_DATA | 1 << SR_LATCH | 1 << SR_CLOCK) ;
        SR_PORT |= 1 << SR_CLEAR;
}
void sr_cleardata(void) {
        SR_PORT &= ~(1 << SR_CLEAR);
        SR_PORT |= 1 << SR_CLEAR;
}

void sr_shiftdata8bit(uint8_t num_shift, uint shift_data) {
        uint8_t i, temp;
        for(i = 0; i < num_shift; ++i) {
                temp = shift_data;
                temp = temp >> i;
                temp &= 0x01;
                if(temp == 0) {
                        SR_PORT &= ~(1 << SR_DATA);
                        SR_PORT |= 1 << SR_CLOCK;
                        SR_PORT &= ~(1 << SR_CLOCK);
                }
                else {
                        SR_PORT |= 1 << SR_DATA;
                        SR_PORT |= 1 << SR_CLOCK;
                        SR_PORT &= ~(1 << SR_CLOCK);
                        SR_PORT &= ~(1 << SR_DATA);
                }
        }
}

void sr_latchdata(void) {
        SR_PORT |= 1 << SR_LATCH;
        SR_PORT &= ~(1 << SR_LATCH);
}

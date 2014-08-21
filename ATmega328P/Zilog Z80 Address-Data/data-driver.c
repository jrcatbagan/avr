// File: main.c
// Created: 15, March 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* This program is for the Atmel AVR Atmega328p. Main task is output an address and
   a particular data based on user inputs to program a memory chip that is used for 
   interfacing with a Zilog Z80 microprocessor */

// Code:

// To-Do List:

/* 1. define the three functions declared (shift functions)
   2. establish the outputs for the LED indicators (i.e. cursor direction and cursor
      location 
   3. code the section on programming the actual data to memory
   4. configure the outputs for the control; this includes read/write, control lines for
      system bus connection, etc.
   5. fix the nested conditions; by the looks of it, if the current system is disconnected
      from the data bus, even if the actual values are modified, the display values will
      not be updated; in other words the logic must be fixed
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#define F_CPU 20000000UL
#include <util/delay.h>  
#include <inttypes.h>

#define SR_DDR   DDRC
#define SR_PORT  PORTC
#define SR_DATA  PINC0
#define SR_LATCH PINC1
#define SR_CLOCK PINC2
#define SR_CLEAR PINC3


void sr_cleardata(void);
void sr_shift8bitval(uint8_t data);
void sr_latchdata(void);

/* Each value in the following array maps a particular digit on a 7-segment display. 
   For convenience, each element is accessed depending on the particular number
   at interest.  E.g. to display a 6 on a 7-segment display, the 6th element in the 
   following array contains the binary map for the digit. */
uint8_t _7segment_binmap[16] = {0X7E, 0x30, 0x6C, 0X79, 0X33, 0X5B, 0X5F, 0X70,
                                0X7F, 0X73, 0X77, 0X1F, 0X4E, 0X7C, 0X4F,};

volatile uint8_t addrdata_numval[6];
volatile enum {HORIZONTAL = 0, VERTICAL} cursor_direction;
volatile enum {D1 = 0, D2, D3, D4, D5, D6} cursor_location;

int main(void) {
        uint8_t digit_selection = 0x20;
        uint8_t digit_dispval[6];
        uint8_t i, pcint0_threshold, pcint1_threshold, pcint2_threshold;
        uint8_t data_line;
        uint16_t address_line;

        pcint0_threshold = pcint1_threshold = pcint2_threshold = 0;
        
        SR_DDR |= (1 << SR_DATA) | (1 << SR_LATCH) | (1 << SR_CLOCK) | (1 << SR_CLEAR);
        SR_PORT &= ~((1 << SR_DATA) | (1 << SR_LATCH) | (1 << SR_CLOCK) | 
                     (1 << SR_CLEAR));

        /* Configure External Interrupt 0 and 1 to trigger on the falling edge */
        EICRA |= (1 << ISC01 | 1 << ISC11);
        /* Enable External Interrupt 0 and 1 */
        EIMSK |= (1 << INT0 | 1 << INT1);
        /* Enalbe Pin Change Interrupt 0 through 2 */
        PCICR |= (1 << PCIE0 | 1 << PCIE1 | 1 << PCIE2);
        /* PCMSK0 range: PCINT0:7 */
        PCMSK0 |= 1 << PCINT;
        /* PCMSK1 range: PCINT8:14 */
        PCMSK1 |= 1 << PCINT;
        /* PCMSK2 range: PCINT16:23 */
        PCMSK2 |= 1 << PCINT;

        /* digit_*val[0] through digit_*val[3] is for the address while 
           digit_*val[4] and digit_*val[5] is for the data */
        for(i = 0; i < 6; ++i) {
                addrdata_numval[i] = 0;
                digit_dispval[i] = _7segment_binmap[0];
        }

        cursor_direction = HORIZONTAL;
        cursor_location = D1;

        mcu_to_systembus == DISCONNECTED;
        
        data_line = address_line = 0;
        sr_cleardata();
        data_line = addrdata_numval[4];
        data_line = data_line << 4;
        data_line |= addrdata_numval[5];
        address_line = addrdata_numval[0];
        address_line = address_line << 4;
        address_line |= addrdata_numval[1];
        address_line = address_line << 4;
        address_line |= addrdata_numval[2];
        address_line = address_line << 4;
        address_line |= addrdata_numval[3];

        sr_shift8bitval(data_line);
        sr_shift16bitval(address_line);

        for(i = 5; i >= 0; --i) {
                sr_shift7bitval(digit_dispval[i]);
        }
        sr_latchdata();
        sr_state = CURRENT;

        while(1) {
                if(mcu_to_systembus == CONNECTED) {
                        if(sr_state == OUTDATED) {
                                data_line = address_line = 0;
                                sr_cleardata();
                                for(i = 0; i < 6; ++i) {
                                        digit_dispval[i] = 
                                                _7segment_binmap[addrdata_numval[i]];
                                }
                        
                                data_line = addrdata_numval[4];
                                data_line = data_line << 4;
                                data_line |= addrdata_numval[5];
                                address_line = addrdata_numval[0];
                                address_line = address_line << 4;
                                address_line |= addrdata_numval[1];
                                address_line = address_line << 4;
                                address_line |= addrdata_numval[2];
                                address_line = address_line << 4;
                                address_line |= addrdata_numval[3];

                                sr_shift8bitval(data_line);
                                sr_shift16bitval(address_line);

                                for(i = 5; i >= 0; --i) {
                                        sr_shift7bitval(digit_dispval[i]);
                                }
                                sr_latchdata();
                                sr_state = CURRENT;
                        }
                        else {
                                if(program_data_tomem == EXECUTE) {
                                        program_data_tomem = HALT
                                }
                        }
                }
        }
        return 0;
}

// Connect and disconnect from the system data bus
ISR(INT0_vect) {
        if(mcu_to_systembus == CONNECTED) {
                mcu_to_systembus = DISCONNECTED;
        }
        else {
                mcu_to_systembus = CONNECTED;
        }
}

// Program into memory
ISR(INT1_vect) {
        if(program_data_tomem == HALT)
                program_data_tomem = EXECUTE;
}

// Direction selection
ISR(PCINT0_vect) {
        if(pcint0_threshold == 0) {
                if(cursor_direction = HORIZONTAL)
                        cursor_direction = VERTICAL;
                else
                        cursor_direction = HORIZONTAL;
                ++pcint0_threshold;
        }
        else {
                pcint0_threshold = 0;
        }
}

// Up/Right
ISR(PCINT1_vect) {
        if(pcint1_threshold == 0) {
                if(cursor_direction == VERTICAL) {
                        switch(cursor_location) {
                        case D1:
                                if(addrdata_numval[0] != 15)
                                        ++addrdata_numval[0];
                                else
                                        addrdata_numval[0] = 0;
                                break;
                        case D2:
                                if(addrdata_numval[1] != 15)
                                        ++addrdata_numval[1];
                                else
                                        addrdata_numval[1] = 0;
                                break;
                        case D3:
                                if(addrdata_numval[2] != 15)
                                        ++addrdata_numval[2];
                                else
                                        addrdata_numval[2] = 0;
                                break;
                        case D4:
                                if(addrdata_numval[3] != 15)
                                        ++addrdata_numval[3];
                                else
                                        addrdata_numval[3] = 0;
                                break;
                        case D5:
                                if(addrdata_numval[4] != 15)
                                        ++addrdata_numval[4];
                                else
                                        addrdata_numval[4] = 0;
                                break;
                        case D6:
                                if(addrdata_numval[5] != 15)
                                        ++addrdata_numval[5];
                                else
                                        addrdata_numval[5] = 0;
                                break;
                        }
                        sr_state = OUTDATED;
                }
                else {
                        switch(cursor_location) {
                        case D1:
                                cursor_location = D2;
                                break;
                        case D2:
                                cursor_location = D3;
                                break;
                        case D3:
                                cursor_location = D4;
                                break;
                        case D4:
                                cursor_location = D5;
                                break;
                        case D5:
                                cursor_location = D6;
                                break;
                        case D6:
                                cursor_location = D1;
                                break;
                        }
                }
                ++pcint1_threshold;
        }
        else {
                pcint1_threshold = 0;
        }
}

// Down/Left
ISR(PCINT2_vect) {
        if(pcint2_threshold == 0) {
                if(cursor_direction == VERTICAL) {
                        switch(cursor_location) {
                        case D1:
                                if(addrdata_numval[0] != 0)
                                        --addrdata_numval[0];
                                else
                                        addrdata_numval[0] = 15;
                                break;
                        case D2:
                                if(addrdata_numval[1] != 0)
                                        --addrdata_numval[1];
                                else
                                        addrdata_numval[1] = 15;
                                break;
                        case D3:
                                if(addrdata_numval[2] != 0)
                                        --addrdata_numval[2];
                                else
                                        addrdata_numval[2] = 15;
                                break;
                        case D4:
                                if(addrdata_numval[3] != 0)
                                        --addrdata_numval[3];
                                else
                                        addrdata_numval[3] = 15;
                                break;
                        case D5:
                                if(addrdata_numval[4] != 0)
                                        --addrdata_numval[4];
                                else
                                        addrdata_numval[4] = 15;
                                break;
                        case D6:
                                if(addrdata_numval[5] != 0)
                                        --addrdata_numval[5];
                                else
                                        addrdata_numval[5] = 15;
                                break;
                        }
                        sr_state = OUTDATED;
                }
                else {
                        switch(cursor_location) {
                        case D1:
                                cursor_location = D6;
                                break;
                        case D2:
                                cursor_location = D1;
                                break;
                        case D3:
                                cursor_location = D2;
                                break;
                        case D4:
                                cursor_location = D3;
                                break;
                        case D5:
                                cursor_location = D4;
                                break;
                        case D6:
                                cursor_location = D5;
                                break;
                        }
                }
                ++pcint2_threshold;
        }
        else {
                pcint2_threshold = 0;
        }
}

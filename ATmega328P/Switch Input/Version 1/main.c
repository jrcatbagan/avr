// File: main.c
// Created: 15, March 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* Takes a switch input to turn on a set of LEDs */

// Code:

#include <avr/io.h>
#define F_CPU 20000000UL
#include <util/delay.h>

#define SWITCH_DDR DDRC
#define SWITCH_PORT PORTC
#define SWITCH_PIN PINC
#define SWITCH_1 PINC0
#define SWITCH_2 PINC1
#define SWITCH_3 PINC2
#define SWITCH_1PIN 0
#define SWITCH_2PIN 1
#define SWITCH_3PIN 2

#define LED_DDR DDRD
#define LED_PORT PORTD
#define LED_1 PIND5
#define LED_2 PIND6
#define LED_3 PIND7

int main(void) {
        enum {NOT_PRESSED = 0, PRESSED} button1_state, button2_state,
                                                button3_state;
        LED_DDR |= ((1 << LED_1) | (1 << LED_2) | (1 << LED_3));
        LED_PORT &= ~((1 << LED_1) | (1 << LED_2) | (1 << LED_3));
        SWITCH_DDR &= ~((1 << SWITCH_1) | (1 << SWITCH_2) | (1 << SWITCH_3));
        button1_state = NOT_PRESSED;
        button2_state = NOT_PRESSED;
        button3_state = NOT_PRESSED;
        while(1) {
                if(bit_is_clear(SWITCH_PIN, SWITCH_1PIN)) {
                        LED_PORT |= 1 << LED_1;
                        button1_state = PRESSED;
                }
                else {
                        LED_PORT &= ~(1 << LED_1);
                        button1_state = NOT_PRESSED;
                }
                if(bit_is_clear(SWITCH_PIN, SWITCH_2PIN)) {
                        LED_PORT |= 1 << LED_2;
                        button2_state = PRESSED;
                }
                else {
                        LED_PORT &= ~(1 << LED_2);
                        button2_state = NOT_PRESSED;
                }
                if(bit_is_clear(SWITCH_PIN, SWITCH_3PIN)) {
                        LED_PORT |= 1 << LED_3;
                        button3_state = PRESSED;
                }
                else {
                        LED_PORT &= ~(1 << LED_3);
                        button3_state = NOT_PRESSED;
                }

                if(button1_state == NOT_PRESSED && 
                   button2_state == NOT_PRESSED && 
                   button3_state == NOT_PRESSED) {
                }
                else if(button1_state == NOT_PRESSED &&
                        button2_state == NOT_PRESSED &&
                        button3_state == PRESSED) {
                        while(bit_is_set(SWITCH_PIN, SWITCH_1PIN) &&
                              bit_is_set(SWITCH_PIN, SWITCH_2PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_3PIN));
                }
                else if(button1_state == NOT_PRESSED &&
                        button2_state == PRESSED &&
                        button3_state == NOT_PRESSED) {
                        while(bit_is_set(SWITCH_PIN, SWITCH_1PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_2PIN) &&
                              bit_is_set(SWITCH_PIN, SWITCH_3PIN));
                }
                else if(button1_state == NOT_PRESSED &&
                        button2_state == PRESSED &&
                        button3_state == PRESSED) {
                        while(bit_is_set(SWITCH_PIN, SWITCH_1PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_2PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_3PIN));
                }
                else if(button1_state == PRESSED &&
                        button2_state == NOT_PRESSED &&
                        button3_state == NOT_PRESSED) {
                        while(bit_is_clear(SWITCH_PIN, SWITCH_1PIN) &&
                              bit_is_set(SWITCH_PIN, SWITCH_2PIN) &&
                              bit_is_set(SWITCH_PIN, SWITCH_3PIN));
                }
                else if(button1_state == PRESSED &&
                        button2_state == NOT_PRESSED &&
                        button3_state == PRESSED) {
                        while(bit_is_clear(SWITCH_PIN, SWITCH_1PIN) &&
                              bit_is_set(SWITCH_PIN, SWITCH_2PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_3PIN));
                }
                else if(button1_state == PRESSED &&
                        button2_state == PRESSED &&
                        button3_state == NOT_PRESSED) {
                        while(bit_is_clear(SWITCH_PIN, SWITCH_1PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_2PIN) &&
                              bit_is_set(SWITCH_PIN, SWITCH_3PIN));
                }
                else if(button1_state == PRESSED &&
                        button2_state == PRESSED &&
                        button3_state == PRESSED) {
                        while(bit_is_clear(SWITCH_PIN, SWITCH_1PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_2PIN) &&
                              bit_is_clear(SWITCH_PIN, SWITCH_3PIN));
                }
        }
        return 0;
}

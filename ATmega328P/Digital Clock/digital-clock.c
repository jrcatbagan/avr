// File: digital-clock.c
// Created 02, April 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* This is the main source file for the program that will operate the digital clock. 
   The hardware that is utilized for the digital clock consist of an Atmel AVR 
   Atmega1284, an HD44780 compatible 16x2 character LCD, and various other components
   such as batteries, buttons, etc. */

// Code:

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#define F_CPU 20000000UL
#include <util/delay.h>
#include "lcd-char.h"

int main(void) {
        lcd_init();

        lcd_display_char(' ');
        lcd_display_char(' ');
        lcd_display_char(0x00);
        lcd_display_char(0x01);
        lcd_display_char(0x01);
        lcd_display_char(' ');
        lcd_display_char(0x04);
        lcd_display_char(' ');
        lcd_display_char(0x00);
        lcd_display_char(0x01);
        lcd_display_char(0x01);
        lcd_display_char(' ');
        lcd_display_char(0x02);
        lcd_display_char(0x01);
        lcd_display_char(0x00);

        lcd_command(lcd_pos17);

        lcd_display_char(' ');
        lcd_display_char(' ');
        lcd_display_char(0x00);
        lcd_display_char(0x03);
        lcd_display_char(0x00);
        lcd_display_char(' ');
        lcd_display_char(0x04);
        lcd_display_char(' ');
        lcd_display_char(0x03);
        lcd_display_char(0x03);
        lcd_display_char(0x00);
        lcd_display_char(' ');
        lcd_display_char(0x03);
        lcd_display_char(0x03);
        lcd_display_char(0x00);
        lcd_display_char('P');
                
        while(1) {
                lcd_command(lcd_pos7);
                lcd_display_char(' ');
                lcd_command(lcd_pos23);
                lcd_display_char(' ');
                _delay_ms(500);
                
                lcd_command(lcd_pos7);
                lcd_display_char(0x04);
                lcd_command(lcd_pos23);
                lcd_display_char(0x04);
                _delay_ms(500);
        }
        return 0;
}

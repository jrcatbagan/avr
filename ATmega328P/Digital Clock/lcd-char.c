// File:lcd-char.c
// Created: 02, April 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* */

// Code:

#define _LCD_VAR_DIS_
#define _LCD_CGRAM_BITMAP_
#include "lcd-char.h"

void lcd_enable() {
        LCD_CONTROL_PORT |= 1 << LCD_EN;
        _delay_ms(2);
        LCD_CONTROL_PORT &= ~(1 << LCD_EN);
}

void lcd_busy_flag_check() {
        LCD_DATA_DDR = 0x00;
        LCD_CONTROL_PORT |= 1 << LCD_RW;
        LCD_CONTROL_PORT &= ~(1 << LCD_RS);
        while(LCD_DATA_PORT >= 0x80) {
                lcd_enable();
        }
        LCD_DATA_DDR = 0xFF;
}

void lcd_command(unsigned char command) {
        LCD_DATA_PORT = command;
        LCD_CONTROL_PORT &= ~(1 << LCD_RW | 1 << LCD_RS);
        lcd_enable();
        LCD_DATA_PORT = 0x00;
        lcd_busy_flag_check();
}

void lcd_write_data(char data) {
        LCD_DATA_PORT = data;
        LCD_CONTROL_PORT &= ~(1 << LCD_RW);
        LCD_CONTROL_PORT |= 1 << LCD_RS;
        lcd_enable();
        LCD_DATA_PORT = 0x00;
        lcd_busy_flag_check();
}

void lcd_display_char(char character) {
        LCD_DATA_PORT = character;
        LCD_CONTROL_PORT &= ~(1 << LCD_RW);
        LCD_CONTROL_PORT |= 1 << LCD_RS;
        lcd_enable();
        LCD_DATA_PORT = 0x00;
        lcd_busy_flag_check();
}

void lcd_display_string(char *string) {
        while(*string != '\0') {
                lcd_display_char(*string);
                ++string;
        }
}

void lcd_cgram_init() {
        unsigned char i, j;
        
        lcd_command(0x40);
        for(j = 0; j < 6; ++j) {
                for(i = 0; i < 8; ++i) {
                        lcd_write_data(custom_char_bitmap[i][j]);
                }
        }
}

void lcd_init() {
        LCD_CONTROL_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN);
        LCD_DATA_DDR = 0xFF;
        _delay_ms(20);

        /* configure the LCD for 8-bit mode and 2 line display */
        lcd_command(0x38);
        _delay_ms(5);
        /* set cursor move direction to increment */
        //lcd_command(0x06);
        _delay_ms(5);
        /* turn on the display with cursor disabled */
        lcd_command(0x0C);
        _delay_ms(5);

        lcd_cgram_init();
        /* clear the 16x2 character LCD screen */
        lcd_command(0x01);
        _delay_ms(5);
}

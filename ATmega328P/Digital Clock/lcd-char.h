// File: lcd-char.h
// Created: 02, April 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Code:

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#include <util/delay.h>

#ifndef _LCD_CONS_
#define _LCD_CONS_
#define LCD_CONTROL_DDR DDRC
#define LCD_CONTROL_PORT PORTC
#define LCD_RS PINC0
#define LCD_RW PINC1
#define LCD_EN PINC2
#define LCD_DATA_DDR DDRD
#define LCD_DATA_PORT PORTD
#endif

#ifndef _LCD_FUNCS_
#define _LCD_FUNCS_
void lcd_enable(void);
void lcd_busy_flag_check(void);
void lcd_command(unsigned char command);
void lcd_write_data(char data);
void lcd_display_char(char character);
void lcd_display_string(char *string);
void lcd_cgram_init(void);
void lcd_init(void);
#endif

#ifdef _LCD_CGRAM_BITMAP_
unsigned char custom_char_bitmap[8][6] =
{{0b00011111, 0b00011111, 0b00011111, 0b00000000, 0b00000000, 0b00000000},
 {0b00011111, 0b00011111, 0b00011111, 0b00000000, 0b00000000, 0b00000000},
 {0b00011111, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00000000},
 {0b00011111, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00001110},
 {0b00011111, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00001110},
 {0b00011111, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00000000},
 {0b00011111, 0b00011111, 0b00000000, 0b00011111, 0b00000000, 0b00000000},
 {0b00011111, 0b00011111, 0b00000000, 0b00011111, 0b00000000, 0b00000000}};
#endif

#ifndef _LCD_VAR_DIS_
#define _LCD_VAR_DIS_

const unsigned char cursor_to_next_line = 0b11000000;

const unsigned char lcd_pos1 = 0x80;
const unsigned char lcd_pos2 = 0x81;
const unsigned char lcd_pos3 = 0x82;
const unsigned char lcd_pos4 = 0x83;
const unsigned char lcd_pos5 = 0x84;
const unsigned char lcd_pos6 = 0x85;
const unsigned char lcd_pos7 = 0x86;
const unsigned char lcd_pos8 = 0x87;
const unsigned char lcd_pos9 = 0x88;
const unsigned char lcd_pos10 = 0x89;
const unsigned char lcd_pos11 = 0x8A;
const unsigned char lcd_pos12 = 0x8B;
const unsigned char lcd_pos13 = 0x8C;
const unsigned char lcd_pos14 = 0x8D;
const unsigned char lcd_pos15 = 0x8E;
const unsigned char lcd_pos16 = 0x8F;
const unsigned char lcd_pos17 = 0xC0;
const unsigned char lcd_pos18 = 0xC1;
const unsigned char lcd_pos19 = 0xC2;
const unsigned char lcd_pos20 = 0xC3;
const unsigned char lcd_pos21 = 0xC4;
const unsigned char lcd_pos22 = 0xC5;
const unsigned char lcd_pos23 = 0xC6;
const unsigned char lcd_pos24 = 0xC7;
const unsigned char lcd_pos25 = 0xC8;
const unsigned char lcd_pos26 = 0xC9;
const unsigned char lcd_pos27 = 0xCA;
const unsigned char lcd_pos28 = 0xCB;
const unsigned char lcd_pos29 = 0xCC;
const unsigned char lcd_pos30 = 0xCD;
const unsigned char lcd_pos31 = 0xCE;
const unsigned char lcd_pos32 = 0xCF;

#endif

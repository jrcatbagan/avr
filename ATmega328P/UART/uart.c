// File: uart.c
// Created: 23, April 2014

/* Copyright (C) 2014, Jarielle Catbagan
 *
 * BSD License
 *
 * Please refer to LICENSE.txt for license details
 */

// Description:

/* configures the ATmega328P for UART communication with a baud rate of 125000 */

// Code:

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char value = 0;
volatile enum {CURRENT = 0, UPDATED} port_status;
volatile char message[] = "LED 1 ON";
volatile enum {PARTIAL = 0, COMPLETE} message_sent;
volatile unsigned char i = 0;

int main(void) {
        DDRC |= (1 << PINC0 | 1 << PINC1 | 1 << PINC2 | 
                 1 << PINC3 | 1 << PINC4 | 1 << PINC5);
        PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 |
                   1 << PINC3 | 1 << PINC4 | 1 << PINC5);
				   
        port_status = CURRENT;
        
        // disable power reduction to USART module
        PRR &= ~(1 << PRUSART0);
        // for asynchronous operation set to normal mode, value for UBRR0 is 
        // determined by UBRR0 = fosc\(16 * BAUD) - 1
        // set the UBRR value to 9 for 125000 baud
        UBRR0H = 0;
        UBRR0L = 0x09;
        // set the USART module to asynchronous operation
        UCSR0C &= ~(1 << UMSEL00 | 1 << UMSEL01);
        // set the asynchronous operation to normal mode
        UCSR0A &= ~(1 << U2X0);
        // set the frame format to 8-bit
        UCSR0B &= ~(1 << UCSZ02);
        UCSR0C |= (1 << UCSZ00 | 1 << UCSZ01);
        // disable the parity generation/detection
        UCSR0C &= ~(1 << UPM00 | 1 << UPM01);
        // set the transmitter to send 2 stop-bits
        UCSR0C |= 1 << USBS0;
        // enable the receiver and transmitter
        UCSR0B |= (1 << RXEN0 | 1 << TXEN0);
        // enable the interrupt when data has been received
        UCSR0B |= 1 << RXCIE0;
        // enable global interrupts
        sei();

        while(1) {
                if(port_status == UPDATED) {
                        switch(value) {
                        case '0':
                                PORTC |= 1 << PINC0;
                                PORTC &= ~(1 << PINC1 | 1 << PINC2 | 1 << PINC3 |
                                           1 << PINC4 | 1 << PINC5);
                                message[4] = '1';
                                break;
                        case '1':
                                PORTC |= 1 << PINC1;
                                PORTC &= ~(1 << PINC0 | 1 << PINC2 | 1 << PINC3 |
                                           1 << PINC4 | 1 << PINC5);
                                message[4] = '2';
                                break;
                        case '2':
                                PORTC |= 1 << PINC2;
                                PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC3 |
                                           1 << PINC4 | 1 << PINC5);
                                message[4] = '3';
                                break;
                        case '3':
                                PORTC |= 1 << PINC3;
                                PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 |
                                           1 << PINC4 | 1 << PINC5);
                                message[4] = '4';
                                break;
                        case '4':
                                PORTC |= 1 << PINC4;
                                PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 |
                                           1 << PINC3 | 1 << PINC5);
                                message[4] = '5';
                                break;
                        case '5':
                                PORTC |= 1 << PINC5;
                                PORTC &= ~(1 << PINC0 | 1 << PINC1 | 1 << PINC2 |
                                           1 << PINC3 | 1 << PINC4);
                                message[4] = '6';
                                break;
                        default:
                                PORTC |= 1 << PINC0;
                                PORTC &= ~(1 << PINC1 | 1 << PINC2 | 1 << PINC3 |
                                           1 << PINC4 | 1 << PINC5);
                                message[4] = '7';
                                break;
                        }
                        port_status = CURRENT;
                        UCSR0B |= 1 << UDRIE0;
                        message_sent = PARTIAL;
                }
        }
        return 0;
}

ISR(USART_RX_vect) {
        value = UDR0;
        port_status = UPDATED;
}

ISR(USART_UDRE_vect) {
        if(message_sent == PARTIAL) {
                if(message[i] != '\0') {
                        UDR0 = message[i];
                        ++i;
                }
                else {
                        message_sent = COMPLETE;
                        i = 0;
                        UCSR0B &= ~(1 << UDRIE0);
                }
        }
}

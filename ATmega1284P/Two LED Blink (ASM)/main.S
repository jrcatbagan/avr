;;; File: main.S
;;; Created: 12, January 2014

;;; Copyright (C) 2014, Jarielle Catbagan
;;;
;;; BSD License
;;;
;;; Please refer to LICENSE.txt for license details

;;; Description:

;;; Code:

.equ  PINB,  0x03
.equ  DDRB,  0x04
.equ  PORTB, 0x05
.equ  PINB0, 0
.equ  PINB1, 1

main:
	ldi 	R16, 0x02
	ldi 	R17, 0x03
	out 	PORTB, R16
	out 	DDRB, R17
	nop

sub:
	ldi	R16, 0x03
	out 	PINB, R16

end: 	nop
	

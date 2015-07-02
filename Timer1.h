/* This header file contains the functions and variables needed to use Timer1
   on the ATMEGA328P chip. This contains 2 functions right now:

1.) Initialization: This functions is extremely simple and just prepares a 
couple registers for the timer and disables global interrupts. 

2.) Setup and Start: This setups up the timer. It turns CTC mode on, sets the 
CS10 and CS12 bits (prescaler of 1024), enables the timer compare interrupt, 
and re-enables global interrupts.

This is NOT a completed library. There is much to be done.

Enjoy. */

#ifndef Timer1_h
#define Timer1_h

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include "Timer1.c"

/* Initialization */
void Timer1_Init();

/* Setup and Start */
void Start(uint32_t count);

#endif //Timer1_h

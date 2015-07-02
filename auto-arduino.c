//#include <stdint.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>
#include "usart.h"

/* Digital pins 8, 9, and 10 are used for controlling.
   Digital pin 11 is a receive pin for the preshow start.

   Pin 8 (PORTB0) is light control
   Pin 9 (PORTB1) is sound control
   Pin 10 (PORTB2) is motor control
   Pin 11 (PORTB3) the preshow start signal

   PORTB0: 0 means dimmed lights, 1 means bright lights
   PORTB1: 0 means ad sound, 1 means movie sound
   PORTB2: 0 means flat, 1 means scope 

   PORTB3: 0 means nothing, 1 means preshow start */

void main(){
  
  unsigned char command;

  uint8_t preshow;

  /* Initialize the USART */
  USART_Init(UBRR);

  /* Initialize the pins */
  DDRB |= ( (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (0<<DDB3) ); //pins 8-10 output, pin 11 input

  while(1){
    
    command = USART_Rec();

    switch(command){

    case 's': //scope start show command: dim lights, change sound, move motor if needed, and enable preshow lock
      
      if(PORTB0 == 1) PORTB0 = 0;
      if(PORTB1 == 0) PORTB1 = 1;
      if(PORTB2 == 0) PORTB2 = 1;
      preshow = 1;

      USART_Trans('S');
      break;

    case 'f': //flat start show command

      if(PORTB0 == 0) PORTB0 = 1;
      if(PORTB1 == 0) PORTB1 = 1;
      if(PORTB2 == 1) PORTB2 = 0;
      preshow = 1;

      USART_Trans('F');
      break;

    case 'e': //end show command: brighten lights, change sound back, move motor for preshow, and disable preshow lock

      if(PORTB0 == 0) PORTB0 = 1;
      if(PORTB1 == 1) PORTB1 = 0;
      if(PORTB2 == 1) PORTB2 = 0;
      preshow = 0;

      USART_Trans('E');
      break;

    case 'c': //end credit command: brighten lights

      if(PORTB0 == 0) PORTB0 = 1;

      USART_Trans('C');
      break;

    case 'p': //preshow start command: this will do nothing but send a letter to the computer to simulate a start preshow signal

      if(preshow == 0 && PORTB3 == 1) USART_Trans('P'); //if the start command has been set ran, you shouldn't be able to see a P.

      break;
      
    default:
      /* do nothing */
      break;

    }
  }
}

      

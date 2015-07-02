/* This program is apart of the Timer1 library */

#include "Timer1.h"

void Timer1_Init(){

  cli(); //disable global interrupts
  TCCR1A = 0;
  TCCR1B = 0;

}

/* Set count to whatever will make the timer create the correct pulse */
void Start(uint32_t count){

  // set compare match register to desired timer count
  OCR1A = count; 

  // turn on CTC mode
  TCCR1B |= (1 << WGM12);

  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);

  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // enable global interrupts
  sei();

}

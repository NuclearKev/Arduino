#include <stdint.h>
#include "usart.h"
#include "Timer1.h"

uint8_t value = 0, i = 0;

void main(){

  unsigned char command;
  uint8_t angle = 0;

  Timer1_Init();

  DDRB   |= ( (1<<DDB3) | (1<<DDB5) );

  TCCR2A |= ( (1<<COM2A1) | (1<<WGM20) );

  TCCR2B |= ( (1<<CS22) );

  OCR2A = 0;

  Start(1000);

  while(1);

}

ISR(TIMER1_COMPA_vect){

  if( i == 0 ){

    OCR2A = value;

    value += 10;

    if( value >= 254 ) i = 1;
    
  }else if( i == 1 ){

    OCR2A = value;

    value -= 10;

    if( value <= 0 ) i = 0;

  }

}

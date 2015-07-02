#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <fftw3.h>

void main(){

  DDRB |= ( (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3) ); //pins 8-10 output

  cli(); //disable global interrupts

  ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    //Prescaler at 128 so we have an 125Khz clock source
  ADCSRB |= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));  //enable free running mode
  ADCSRA |= (1<<ADATE);  //enable auto trigger
  ADCSRA |= (1<<ADIE);   //enable ADC interrupts            
  ADCSRA |= (1<<ADEN);   //Power up the ADC

  DIDR0  |= 0x01;      //turn off digital power on A0

  sei(); //enable global interrupts

  ADCSRA |= (1<<ADSC);  //Start converting

  while(1);

}

/* This function is ran when the ADC interrupt flag is high */
ISR(ADC_vect){

  uint16_t value = ADCW;

  if(value <= 256 && value > 50)        PORTB = 0x01;
  else if(value > 256 && value <= 512)  PORTB = 0x03;
  else if(value > 512 && value <= 768)  PORTB = 0x07;
  else if(value > 768 && value <= 1023) PORTB = 0x0F;
  else if(value <= 50)                  PORTB = 0x00;

}



#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

int main(void){

  USART_Init(UBRR);

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
  
  unsigned char data;

  data = (char) ADCW;

  USART_Trans(data);

}

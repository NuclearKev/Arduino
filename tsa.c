/*
Copyright(c) 2015 Kevin Bloom

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.


Rundown:

 *Green LEDs are tied to PORTB pins
 *Red LEDs are tied to PORTx pins
 *Pin 13 will NOT be used but 5-12 will be
 *The volume intensity is opposite of the pin numbers
  -Pin 12 is the lowest LED, Pin 8 is the last green, and Pin 5 is the max

 */

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void main(){

  /* sets pins 8-12 as outputs */
  DDRB = 0x1F;
  /* sets pins 5-7 as outputs */
  DDRD = 0xE0;

  /* disable global interrupts */
  cli();

  /* Prescaler at 128 so we have an 125Khz clock source */
  ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    
  /* enable free running mode */
  ADCSRB |= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
  /* enable auto trigger */
  ADCSRA |= (1<<ADATE);
  /* enable ADC interrupts */
  ADCSRA |= (1<<ADIE);
  /* Power up the ADC */
  ADCSRA |= (1<<ADEN);
  /* turn off digital power on A0 */
  DIDR0  |= 0x01;

  /* enable global interrupts */
  sei();
  /* Start converting */
  ADCSRA |= (1<<ADSC);  

  while(1);

}

/* This function is ran when the ADC interrupt flag is high */
ISR(ADC_vect){

  uint16_t value = ADCW;

  if     (value > 10  && value <= 128)  PORTB = 0x10, PORTD = 0x00; //LED 1 on
  else if(value > 128 && value <= 256)  PORTB = 0x18, PORTD = 0x00; //LEDs 1-2 on
  else if(value > 256 && value <= 384)  PORTB = 0x1C, PORTD = 0x00; //LEDs 1-3 on
  else if(value > 384 && value <= 512)  PORTB = 0x1E, PORTD = 0x00; //LEDs 1-4 on
  else if(value > 512 && value <= 640)  PORTB = 0x1F, PORTD = 0x00; //LEDs 1-5 on
  else if(value > 640 && value <= 768)  PORTB = 0x1F, PORTD = 0x80; //LEDS 1-6 on
  else if(value > 768 && value <= 896)  PORTB = 0x1F, PORTD = 0xC0; //LEDs 1-7 on
  else if(value > 896 && value <= 1023) PORTB = 0x1F, PORTD = 0xE0; //All LEDs on
  else if(value <= 10)                  PORTB = 0x00, PORTD = 0x00; //All LEDs off

}



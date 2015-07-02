/* The purpose of this program is to show off all the cool things
that I've accomplished with AVR.

You can comment out the functions you don't want to use, otherwise,
you will only see the first one in action due to the infinte while
loops. 

For the USART function, it is best to see using GNU Screen or whatever.

Enjoy. */


#include "usart.h"
#include "Timer1.h"

void USART();
void Timer1();

volatile uint8_t *led = (uint8_t *)0x25;
volatile uint8_t *inout = (uint8_t *)0x24;
uint8_t i = 0;


int main(){

  //  USART();

  Timer1();
 
}

void USART(){

  USART_Init(UBRR);

  while(1) USART_Trans(USART_Rec());

}

void Timer1(){

  *inout = 1<<5;

  Timer1_Init();

  Start(FOSC); //FOSC is declared in usart.h

  while(1);

}

/* This is an interrupt detection function from the interrupt.h file. It is 
   being used here to make the on-board LED (on the Arduino Uno) blink. */
ISR(TIMER1_COMPA_vect){

  if(i == 0) *led = 0<<5 ,i=1;
  else       *led = 1<<5 ,i=0;

}

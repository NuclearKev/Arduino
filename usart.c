/* This is apart of the USART library for the ATMEGA328P chip. Enjoy */

#include <stdlib.h>
#include "usart.h"

void USART_Init(uint16_t ubrr){

  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);

}

void USART_Trans(unsigned char data[], uint64_t size){
  
  uint64_t i;

  for(i = 0; i < size; i++){
    /* Wait for the transmit buffer to be empty */
    while( !( UCSR0A & (1<<UDRE0) ) );
    /* Puts data into the transfer buffer, send data */
    UDR0 = data[i];
    
  }
}

unsigned char *USART_Rec(uint64_t bytes){

  unsigned char *ReceiveBuffer = (unsigned char*)malloc(sizeof(unsigned char)*bytes); //allocates space for the array
  uint64_t i;

  for(i = 0; i < bytes; i++){
    /* Wait for data */
    while( !(UCSR0A & (1<<RXC0)) );
    /* Put data into buffer */
    ReceiveBuffer[i] =  UDR0;
  }

  return ReceiveBuffer;
}

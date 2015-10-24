/* This is the header file that contains three functions:

1.) USART initialization: This initializes the USART so that you can use it. 
It must be done in order to use it. Also, you can modify the FOSC, BAUD, and
UBRR according to your set up. This function also enables BOTH transmitting 
and receiving so merry Christmas. Lastly, this function sets up the USART to
use 8-bit data and 2 stop bits. Look your chips documentation otherwise.

2.) USART Transfer: This transfers some data, obviously. This function is
pretty straight foreword and all it does it transmit. You can transfer multiple
bytes of data by using an array.

3.) USART Receive: This receives data from some external source. Once again,
this is straight foreward and all it does is receive. 

Enjoy. */

#ifndef usart_h
#define usart_h

#include <avr/io.h>
#include <stdint.h>
#include "usart.c"

#define FOSC 16000000 //clock speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

/* Initialization */
void USART_Init(uint16_t ubrr);

/* Transfer  */
void USART_Trans(unsigned char data[], uint64_t size);

/* Receive */
unsigned char *USART_Rec(uint64_t bytes);

#endif //usart_h

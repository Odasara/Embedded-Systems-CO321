#include <avr/io.h>

/** Baud rate = fosc/(16*(x+1))
9600 = 16M/16(x+1)
x = 103.166 ~ 103  **/

void usart_init(){
	UCSR0B  |= (1 << RXEN0 ); 		// Enable the USART receiver
	UCSR0B  |= (1 << TXEN0 ); 		// Enable the USART transmitter
	
	UCSR0C &= ~(1<<UPM01 | 1<<UPM00);	//No parity
	UCSR0C &= ~(1<<USBS0);				//1 stop bit
	
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);  //8 bit data frame
	UCSR0B &= ~(1<<UCSZ02);
	
	UBRR0 = 103;  					 //set baud rate
}

void usart_send (char data){
	while (!(UCSRA & (1<<UDRE0))){    //wait until UDRE0 bit is set
	}
	UDR0 = data;					//character is written to UDR0 register
}

char usart_receive(){
	while ((UCSRA & (1 << RXC0)) == 0){   //wait until RXC0 is set
	} 
	return UDR0;      //return the received character
}

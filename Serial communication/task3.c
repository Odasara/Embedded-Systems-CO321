#include <avr/io.h>

void usart_init(){
	UCSR0B  |= (1 << RXEN0 ); 		// Enable the USART receiver
	UCSR0B  |= (1 << TXEN0 ); 		// Enable the USART transmitter
	
	UCSR0C &= ~(1<<UPM01 | 1<<UPM00);	//No parity
	UCSR0C &= ~(1<<USBS0);				//1 stop bit
	
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);  //8 bit data frame
	UCSR0B &= ~(1<<UCSZ02);
	
	UBRR0 = 103;   	//set baud rate tom 9600
}

void usart_send (char data){
	while (!(UCSR0A & (1<<UDRE0))){    //wait until UDRE0 bit is set
	}
	UDR0 = data;		//character is written to UDR0 register
}

char usart_receive(){
	while ((UCSR0A & (1 << RXC0)) == 0){   //wait until RXC0 is set
	} 
	return UDR0;      //return the received character
}

int main(){
	unsigned char ch ;
	usart_init();
	while(1){
        char ch='\0';
        while(ch!= '\r'){    //loop till carriage return is received
        	//recieving a character
			ch=usart_receive();
      
	        if(ch>='A' && ch<='Z'){		//whether alphabatical and capital
					ch =(char)((ch-'A'+3)%26+'A');		//getting the cipher
				
			}
			else if(ch>='a' && ch<='z'){      //whether alphabatical and simple
					ch =(char)((ch-'a'+3)%26+'a');
					
			}
			else{
				ch=ch;
			}
	    
	        usart_send(ch);     //send the character(encrypted)
        
		}
	}
	
	
	return 0;
}










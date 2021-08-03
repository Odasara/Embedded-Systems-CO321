#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char counter = 0;	//global variable counter

int main(void)
{
  DDRB = DDRB | 0x01; //set pin0 of portB as output
  PORTB = PORTB | 0x01; //set the bit 1initially
  
  TCNT0 = 0x06;			//initial value in timer register=6
 
 
  //set the TIMER0 under normal mode with 1:256 prescaler
  TCCR0A = 0x00;//normal mode
  TCCR0B = 0x04;//1:256 scale  
   
  sei(); //enable global interrupts(set I)
  
  TIMSK0 |= (1<<TOIE0);; //enable Timer0 overflow interrupt
 
 
  while(1){
  }  			 //infinite loop

    return 0;
}


ISR(TIMER0_OVF_vect){
  TCNT0 = 0x06;			//reload for next round
  counter++;			//couter is incrementing
  
  if (counter == 25){
    PORTB = PORTB^(1<<0);	//toggling after 100ms
    counter = 0;			//counter is set to zero
  } 
}


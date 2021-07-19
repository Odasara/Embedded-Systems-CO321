#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

int main(void){
  DDRD = DDRD & ~(1<<2); //initialize Port D pin 2 as input
  DDRB = DDRB | (1<<0);  //initialize PORT B pin 0 as output
  
  //set the falling edge
  EICRA |= (1<<ISC01);		  //set ISC01 to 1
  EICRA &=~(1<<ISC00);        //set ISC00 to 0
  
  sei();                   //Enable global interrupts
  
  EIMSK |= (1<<INT0); //Enable external hardware interrupts for INT00
  
  while(1){     //to stop ending the main
  }
  return 0;
    
}

ISR (INT0_vect){   
    PORTB = PORTB^(1<<0); //toggle the PB0 pin
  _delay_ms(500);
}


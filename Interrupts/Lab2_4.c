#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>



int main (void){
  	DDRB = DDRB|0xFF;	  //initialize 	 Port B as output
  	DDRD = DDRD &~(1<<2);	  // initialize pin 2 of PORTB as input
  	DDRD = DDRD &~(1<<3); //initialize pin 3 of PORTB as input
  //set the rising edge detection
  	EICRA |= (1<<ISC01);  //set ISC01 to 1
  	EICRA |= (1<<ISC00);  //set ISC00 to 1
  
  	EICRA |= (1<<ISC11);  //set ISC11 to 1
  	EICRA |= (1<<ISC10);  //set ISC10 to 1
  	
  	sei();   //enable global interrupts
  	EIMSK |= (1<<INT0);	//enable external hardware interrupt for INT00
  	EIMSK |= (1<<INT1);	//enable external hardware interrupt for INT1
  
  
  	while(1){   //loop till last led
  	}
  	return 0;  
}
int z=0;
//led off
ISR(INT0_vect){   //ISR for INT0
  z=z<<1;  //left shifted z by 1
  PORTB = PORTB &~ 0xFF;  //turn off
  PORTB = PORTB | z;    //asign portB|z to portB
   
}
//led on
ISR(INT1_vect){    //ISR for INT1
  z=(z<<1)+1;   //z value is left shifted by 1 and then added 1
  PORTB = PORTB &~ 0xFF;
  PORTB = PORTB | z;   //asign portB|z to portB
  
}           









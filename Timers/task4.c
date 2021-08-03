#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main (void){
	
  
  DDRB = DDRB | (1<<5);							//set pin 5 of PORTB for output for led toggle
  DDRB = DDRB | (1<<0)|(1<<1)|(1<<2)|(1<<3);  //set first 4 pins of PORTB for output fro knight rider cct
  							
  PORTB = PORTB & ~(PORTB);				//set Port B value to zero initially
  
  TCNT1 = 0x0BDC;			//initial value-3036
  
  TCCR1A = 0x00;	//Set Timer1 under nnormal mode 
  TCCR1B =0x04;		//set precaler 1:256
  
  sei();			//enable global interrupts
  
  TIMSK1 |= (1<<TOIE1);	//enable Timer1 overflow  interrupt-timer 1
  
  //Knight rider circuit
  
  unsigned char i;		//declaring i variable
  while(1){
        
    for ( i=0 ; i < 4 ; i++){						//loop i from 0 to 3
  
    	PORTB = PORTB | (1<<i);						//set pin i high to turn led on
     	_delay_ms(1000);							//delay
    	PORTB = PORTB &~(1<<i);						//set pin i low to turn led off
    
  	}
  
   	for ( i=0 ; i < 2 ; i++){						//loop i from 0 to 1
    
  		PORTB = PORTB | (4>>i);						//set pin i high to turn led on
     	_delay_ms(1000);							//delay
    	PORTB = PORTB &~(4>>i);						//set pin i low to turn led off
    
  	}
  
  }
  
  return 0;
  
}


ISR (TIMER1_OVF_vect){
  
  TCNT1 =3036;						//reload for next round
  PORTB = PORTB ^ (1<<5);			//toggle PB5
   
}


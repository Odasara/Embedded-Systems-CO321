#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char c = 0;

int main(void){
  
  DDRB = 0x0F; 					//initialize portB as output
  PORTB = PORTB & ~(PORTB);  //pins set to 0
  
 
  TCNT0 = 0x83;			//timer 0-initial value = 131
  TCNT1 = 0x85EE;		//timer 1-initial value= 34286
  
  //for timer 0
  TCCR0A = 0x00;			//normal mode
  TCCR0B = 0x04;  		 //prescaling to1:256
  
  //for timer 1
  TCCR1A = 0x00;			//normal mode
  TCCR1B = 0x04;   		//prescaling to 1:256
  
  sei();				 //enable global interrupts
  
  TIMSK0 |= (1<<TOIE0); //enable Timer0 overflow interrupt-timer 0
  TIMSK1 |= (1<<TOIE1);//enable Timer1 overflow interrupt-timer 1

  while(1){
  }      		//to stop terminating main

  return 0;
  
}


ISR(TIMER0_OVF_vect){           //ISR for timer0
  TCNT0 = 0x83;              //reload for next round
  c++;                   //increment loop
  if (c == 25){
    PORTB = PORTB^(1<<1);    //toggling after 50ms
   	c = 0;             //loop set to 0
  }
}


ISR(TIMER1_OVF_vect){  			//ISR for timer 1
  TCNT1 = 0x85EE;				//reload for next round
  PORTB = PORTB ^ (1<<0);		//0th pin is toggled   
}



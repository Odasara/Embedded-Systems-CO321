#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>

unsigned char z=0;

int main(void){
  //initialize input and output ports
  DDRB = DDRB |(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);
  DDRD = DDRD & ~(1<<2);
  //set falling edge detection
  EICRA |= (1<<ISC01);
  EICRA &= ~(1<<ISC00);
  
  sei();  			//enable global interrupts
  
  EIMSK |= (1<<INT0);  //enable hardware interrupts for INT0
  
  while(1){
  }  			//loop to stop terminating the main
  return 0;  
}
//isr for the interrupt
ISR(INT0_vect){
  z+=1;       //increment counter
  PORTB = z;
  _delay_ms(500);
}


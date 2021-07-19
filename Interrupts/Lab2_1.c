#include <avr/io.h>
#include <util/delay.h>

int main(void){
  unsigned char z=0;
  DDRD = DDRD & ~(1<<7);  //initialize 7th pin of port D as input
  DDRB = DDRB | 0xFF;   //Initualize Port B as output
  
  while (1){            //infinite loop
    if(PIND & (1<<7)){  //check whether the input is 1 or 0
    
    	z=z+1;              //increment the counter by 1
      	PORTB= z;         //assign the counter value to PORTB
      	_delay_ms(500);   //stay for the delay 
      
 
      	while(PIND & (1<<7)){ //empty loop till the pushbutton is released
      	}    
    }    						
  }  
  return 0;
}

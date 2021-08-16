#include <avr/io.h>
#include <util/delay.h>

unsigned char i;

int main(void){
 
  DDRD = DDRD|(1<<6);		//set oc0A pin as output (PD6)
 
  TCCR0B |= (1 << CS01) | (1 << CS00);		 // set prescaler to 64
  TCCR0A |= (1 << COM0A1); 					// set non-inverting mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00);	 // set fast PWM Mode
 
  while(1){			 //infinite loop to stop terminating the program
    //fade from off -> on
    for (i=0 ; i<256 ; i++){
      OCR0A = i; 	//increments
      _delay_ms(20);  //delay 
    }
   
    //fade from on -> off
    for (i=255; i>=0; i--){
      OCR0A = i; 		//decrements
      _delay_ms(20); 	 //delay
    }  
  }
 
  return 0;
}


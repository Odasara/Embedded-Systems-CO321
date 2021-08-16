#include <avr/io.h>
#include <util/delay.h>

/*
get appropriate frequencies in between 20-20000Hz
f(generated wave) = (16*10^6)/(256 x N)
 
when N = 1024
f(generated wave) = 61.035Hz
 
N = 256
f(generated wave) = 244.140Hz
 
N = 64
f(generated wave) = 976.5Hz
 
N = 8
f(generated wave) = 7812.5Hz

*/
unsigned char i;

int main(void){
  
  DDRD = DDRD|(1<<6);		//setting the 6th pin as output
  
  OCR0A = 127;				//50% duty cycle
  TCCR0A |= (1 << COM0A1); 	// set non-inverting mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00); 	// set fast PWM Mode
   
  while(1){ 
    
    for (i = 5;i>=2;i--){ //loop starts from 5(1:1024) to 2(1:8)
      TCCR0B = i;	    //assign coressponding value to TCCR0B bit	   
      _delay_ms(1000);		//stay for delay
    }
    
  }
  return 0;
}



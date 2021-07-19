#include <avr/io.h>   
#include <util/delay.h>

int main (){
  DDRB = 0x0F;    //initialize PORTB as an output port
 
/*  while(1){        //infinite loop
    PORTB = 0x0F;    //Turn ON LEDs
    _delay_ms(1000);  //1000ms delay
    PORTB = 0x00;    //Turn OFF LEDs
    _delay_ms(1000);  //1000ms delay
  }  
  return 0;*/
  
  while(1){
  
  PORTB= PORTB ^ ((1)|(1<<1)|(1<<2)|(1<<3));
    _delay_ms(1000);
  }
}
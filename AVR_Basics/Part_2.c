#include<avr/io.h>
#include<util/delay.h>   //headers

int main(){
  
  DDRB = 0x0F;      //Initialize PORTB as an output port
  
  while(1){       //Infinite loop

  for(int i=0;i<4;i++){    //loop for 4
   	PORTB = 1<<i;  //Left shift 00000001 by i and asign it to PORTB
   _delay_ms(500);   //Delay of 500ms 
   }
    
  for(int i=0;i<2;i++){  //backword loop
    PORTB = 4>>i;     //Right shift 00001000 by i and asign it to PORTB
     _delay_ms(500);   //Delay of 500ms
   }
    
  }  
  
}
#include<avr/io.h>
void delay_timer0(){

  TCNT0 = 131;                  //load timer counter with initial value 131

  TCCR0A = 0b000;               //set normal mode
  TCCR0B = 0b100;               //set cs bits to 110(x256 scale)

  while((TIFR0 & 0b01)==0);     //wait till timer overflow bit(TOV0) is set

  TCCR0A = 0x00;                //clear timer settings
  TCCR0B = 0x00;

  TIFR0 = 0x01;                 //clear overflow flag(timer overflow)
}

int main(void){

  DDRB = DDRB|(1<<5);           //configure PB5 as output pin

  while(1){
    PORTB = PORTB ^ (1<<5);     //toggle the 5th pin in portB
    for(int i=0;i<250;i++){     //loop 250 times to get 500ms delay
         delay_timer0();
    }
  }

  return 0;
}



#include <avr/io.h>

int main(void){
 
  DDRD = DDRD|(1<<6);		//Initialize OCR0A pin as output
 
/*
  Calculate OCR0A value to get 50% duty cycle
  
  Duty cycle = ((ocr0 + 1)/256)*100
  50 = 100(1+ocr0) / 256
  ocr0 = 127
*/
  OCR0A = 127; //assign calculated ocr0 value

/*
  Calculate the Prescalar(N)
  
  F(generated wave) = F(timerclock)/256
  F(timerclock) = F(oscillator) / N
  N = F(oscilator)/F(generated wave)x 256
 
  N = 16*(10^6) / (976.56 x 256)
  N ~= 64
 
*/
  
  TCCR0B |= (1 << CS00) | (1 << CS01); // set prescaler to 64
  
  //configure PWM settings
  TCCR0A |= (1 << WGM01) | (1 << WGM00); // set fast PWM Mode
  TCCR0A |= (1 << COM0A1); // set non-inverting mode
 
  while (1);	//loop to prevent program from ending
   
  return 0;
 
}


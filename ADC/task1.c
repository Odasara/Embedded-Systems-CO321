#include <avr/io.h>
#include <math.h>

unsigned int i;	//increment
unsigned int out; 	//keep the total decimal value


int main(void){

	/** Pre scalar calculation
	XTAL = 16MHz
    f(ADC) = f(Osc)/Prescalar
    f(ADC) < 200kHz for the maximum accuracy
    200*10^3 = 16*10^6 / prescalar
    Prescaar = 80  ---> minimum prescalar
    
    Let's take prescalar as 128
    So, f(ADC) = 16MHz/128 = 125KHz
**/

	DDRD = 0xFF;	//setting PORTD as output
	DDRC = DDRC &~(1<<1);  //setting ADC1 pin as input(PC1)
	
 	//enable ADC (ADEN (bit7) in ADCSRA reg)
  	ADCSRA |= (1<<ADEN);
 
    //set prescalar(conversion time)
  	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADCSRA[2:0] = 111 for 128 prescalar
      
  	//set AVCC as the reference voltage for ADC 
    ADMUX = ADMUX | (1<<REFS0);   //REFS0 = 1
  	ADMUX = ADMUX &~(1<<REFS1);   //REFS1=0
      
    //left justify results
    ADMUX = ADMUX |=(1<<ADLAR);   //ADLAR=1
  	    
    ADMUX |= 0x01;			//select analog input channel ADC1 = MUX[3:0] = 0b0001
    ADCSRA |=(1<<ADSC);		//activate start conversion bit
    
  	while(1){
  		
  		while((ADCSRA & (1<<ADIF))==0);	//wait until Interrupt flag is set and conversion is completed
       
      	//find the decimal out value using ADCL and ADCH
      /*  for (i = 0; i < 8; i++)
        {
          if((ADCH>>i)&1){  //first 8 bits
            out += pow(2,i-6);  
          }
          if((ADCL>>i)&1){  //last 2 bits
            out += pow(2,i+2);  
          }
        } */
		 
        for (i=0;i<=7;i++){
        	if((ADCH>>i) & 1){
        		out+= pow(2,i+2);
			}
		}
		for (i=6;i<=7;i++){
			if ((ADCL>>i) & 1){
				out+= pow(2,i-6);
			}
		}
      
      //calculate the relative out value wrt 8 LEDs 
      out = (out*8)/1023;
    
      //turn on LED portion
      for (i = 0; i < out; i++)
      {
         PORTD |= (1<<i) ;
      } 
  	}

  return 0;
}


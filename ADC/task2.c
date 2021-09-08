#include <avr/io.h>

/**	XTAL = 16MHz
    f(ADC) = f(Osc)/Prescalar
    f(ADC) < 200kHz for the maximum accuracy
    200*10^3 = 16*10^6 / prescalar
    Prescaar = 80  ---> minimum prescalar
    
    Let's take prescalar as 128
    So, f(ADC) = 16MHz/128 = 125KHz
**/
int main (void){
	DDRB = (1<<0);		//set portB pin0 as output
	DDRC = DDRC &~(1<<1);  //set ADC1 pin as input (PC1)
	
	//enable ADC (ADEN (bit7) in ADCSRA reg)
  	ADCSRA |= (1<<ADEN);
 
    //set prescalar(conversion time)
  	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADCSRA[2:0] = 111 for 128 prescalar
  	
  	//Turn off internal vref (External AREF is used as voltage reference)
  	//ADMUX = ADMUX | (1<<REFS0); 
    ADMUX = ADMUX &~(1<<REFS0);   //REFS0=0
  	ADMUX = ADMUX &~(1<<REFS1);   //REFS1=0
  	
  	
    //left justify results
    ADMUX |=(1<<ADLAR);   //ADLAR=1  	
    
    ADMUX |= 0x01;		//select analog input channel ADC1 = MUX[3:0] = 0b0001
    
    
    while(1){
    	ADCSRA |=(1<<ADSC); 	//activate start conversion bit
    	while((ADCSRA & (1<<ADIF))==0);	//wait until Interrupt flag is set and conversion is completed
    	
    	
    	if (ADCH < 127){		//used 1k as resistor(This value may vary wrt light intensity)
        	PORTB = (1<<0);		//turn on the led
    	}
    	else{ 
        	PORTB =(00);		//turn off the led
    	}
      	
	}
	
	return 0;
   
}


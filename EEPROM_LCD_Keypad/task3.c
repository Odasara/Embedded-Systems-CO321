#include <stdio.h>
#include <avr/io.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

// configure the pins with the ports in LCD 
LiquidCrystal lcd(9, 8, 2, 3, 4, 5);

//15 characters used for alphabet
char alphabet[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','#'};

//key mapping chart
char hexaKeys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


// array used to hold the pins and ports
int inpArr[4] = {2, 3, 4, 5};

//function to initialize keypad
void initKeyPad() {
  
  DDRC |= 0b00001111;		//set PC0-3 as output pins	(as rows)
  //DDRC &= ~(0b00110000);	//set PC4-5 as input pins 	(as columns)
  DDRB &= ~(0b00111100);    //set PB2-5 as input pins	(as columns)
}


// To return the encrypted key
void encrypt(char *str, int secret_key)
{
    int n = 0, idx = 0;
    char *p = str;
	// go until the input string index ends
    while(*p){
       //if(p == '') break;
      	// get the alphabatic index of the current char
       int i = 0;
    	// go through the alphabet and get the index
    	for(i = 0; i < 15; ++i){
        	if(alphabet[i] == *p) break;
   		}
        idx = (i + secret_key) % 15; 
        // display the encrypted char
      	lcd.setCursor(n, 1);
     	lcd.print(alphabet[idx]);
        n++;	//increment cursor
        p++;	//increment pointer to go to next character
    }
}

//keypad scan for finding pressed keys
char scanKeyPad() {
  
  // loop until an input found
  //PORTC =0;
  while (1) {
    for (int i = 0; i < 4; i++){
      // clear all the lines
      PORTC &= 0b11110000;
      // Setting High the corresponding line
      PORTC |= 1<<(i);

      // checking for Inputs
      for (int j = 0; j < 4; j++) {
       if ((PINB>>inpArr[j])&1){
            _delay_ms(200);
            return(hexaKeys[i][j]);
       }
     }
    }
  }
}



int main(){

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //initialize keypad
  initKeyPad();
  
  char index, input;
  
  int key = EEPROM.read(0);
  
  char plain_text[10];
  char encrypted[10];
    
  //loop infinitely 
  while(1){
    lcd.clear();
 	lcd.setCursor(0,0);
	// select from encrpyt and key change 
	lcd.print("1-Encrypt");
    lcd.setCursor(0, 1);
    lcd.print("2-Change key");
    
    // take the input
    input = scanKeyPad();
    
    //screen clear after input taken
    lcd.clear();
    
    if(input == '1'){
   	  lcd.setCursor(0, 0);
      lcd.print("Enter:");
      
      input = '0';
      int cursorX = 0;
  	  int cursorY = 1;
      
      index = 0;
      lcd.setCursor(0, 1);
      
      // loop until a star
      while(input != '*'){
      	input = scanKeyPad();
        lcd.print(input);
        cursorX++;
        
        // add to plain text array
        plain_text[index] = input;
        index++;
        
        // break loop when 10 characters counted(MAX)
        if(index > 9){
        	break;
        }
        
        lcd.setCursor(cursorX, cursorY);
      }
     
     plain_text[index] = '*';
     lcd.clear();
		
     lcd.setCursor(0, 0);
     int key = EEPROM.read(0);
     lcd.print("EncryptedText: ");
    
     lcd.setCursor(0, 1);
     // encrypt and display the text
     encrypt(plain_text, key);
     
     // wait for the next character 
     scanKeyPad();  
      
    } else if(input == '2'){
      //key = 0;
      // get the user input key
      lcd.setCursor(0, 0);
      lcd.print("Enter key:");
      lcd.setCursor(0, 1);
      lcd.print("__");
      
      // get the secret key
      input = scanKeyPad();
      lcd.setCursor(0, 1);
      lcd.print(input);
      // get the first digit
      key += (input-'0')*10;
        
      _delay_ms(100);
      // get input for second digit
      input = scanKeyPad();
      lcd.setCursor(1, 1);
      lcd.print(input);
      key += (input-'0');
      // write key in to EEPROM
      EEPROM.write(0,key);
        
    }else{
        // Display error for invalid entry
    	lcd.setCursor(1, 0);
      	lcd.write("Error");
      	_delay_ms(500);
      	lcd.clear();
    }
    _delay_ms(100);
  
}
 return 0;

}

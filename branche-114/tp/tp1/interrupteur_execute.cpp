#define F_CPU   8000000UL
#include <util/delay.h>
#include <avr/io.h> 



int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  
   
    for(;;){
      
      if(PIND & 0x04) {
        _delay_ms(10);//rebound
        if(PIND & 0x04){
          PORTC = 0b01;
          _delay_ms(5);
          PORTC = 0b10;
          _delay_ms(5);          
        }     
      } 
      PORTC = 0b00;  
    }   

  return 0; 
}


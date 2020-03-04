#define F_CPU   8000000UL
#include <util/delay.h>
#include <avr/io.h> 



int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie
   
    for(;;){
    PORTB=0b01;
    _delay_ms(4000);
        
    PORTB=0b10;
    _delay_ms(4000);

    for(int i = 0; i < 200; i++){
      PORTB = 0b01;
      _delay_ms(10);
      PORTB = 0b10;
      _delay_ms(10);
    }
    
    }
    

  return 0; 
}


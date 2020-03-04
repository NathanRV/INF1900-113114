#include <avr/io.h>
#include <util/delay.h>


bool debounce() {
    uint8_t temp0 = PIND;
    _delay_ms(10);
    uint8_t temp1 = PIND;
    return temp0 == temp1;
}

int main(){
    DDRD = 0x00;
    DDRB = 0xff;
    
    for (;;) 
    {
        if(PIND & 0x04 && debounce())
        {   
            _delay_ms(5);
            PORTB = 0b10;
            _delay_ms(5);
            PORTB = 0b01;

        } else
        {
            PORTB = 0b00;
        }      
    }
}
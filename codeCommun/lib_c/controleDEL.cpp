#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB = 0xff;
    for(;;){
        _delay_ms(5);
        PORTB = 0b01;
        _delay_ms(5);
        PORTB = 0b10;
    }
}

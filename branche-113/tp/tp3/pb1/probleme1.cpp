#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>

int main() {
    DDRB = 0xff;

    for(int i = 0; i < 3000; i++) {
        PORTB = 0x01;
        for(int j = 0; j < 1000-i; j++) {
            _delay_us(1);
        }
        PORTB = 0x00;
        for(int k = 0; k < i; k++) {
            _delay_us(1);
        }
    }
}
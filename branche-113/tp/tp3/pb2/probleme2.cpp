#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>


int main() {
    DDRB = 0xff;
    int total = 1000;
    int runTime = 0;
    for(;;) {
        // for(int i = 0; i < 3000; ++i) {
        PORTB = 0x02;
        for(int j = 0; j < runTime; j++) {
            _delay_us(1);
        }
        PORTB = 0x00;
        for(int k = 0; k < (total - runTime); k++) {
            _delay_us(1);
        }
        // }
        runTime += 250;
    }
}

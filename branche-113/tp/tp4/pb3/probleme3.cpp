#define F_CPU 8000000 

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

void ajustementPWM (uint8_t intensite) {
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)
    OCR1A = intensite;
    OCR1B = intensite;
    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1A = (1 << WGM10 | 1 << COM1A0 | 1 << COM1A1);
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
}

void initialisation() {
    cli();
    DDRD = 0xFF;
    sei();
}

int main() {
    initialisation();
    while(1){
        ajustementPWM(0);
        _delay_ms(2000);
        ajustementPWM(128);
        _delay_ms(2000);
        ajustementPWM(191);
        _delay_ms(2000);
        ajustementPWM(255);
        _delay_ms(2000);
    }
    return 0;
}
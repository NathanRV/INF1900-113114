#define F_CPU 8000000 
#define ISR_BLOCK

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR(TIMER1_COMPA_vect) {
    minuterieExpiree = 1;
}

ISR(INT0_vect) {
    boutonPoussoir = 1;
    //anti-rebond
    _delay_ms(30);
}

void partirMinuterie (uint16_t duree) {
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << CS10) | (1 << CS12);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A) ;
}

void initialisation(void) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRB = 0xff;
    DDRD = 0x00;
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

int main() {
    initialisation();
    _delay_ms(10000);
    PORTB = 0x02;
    _delay_ms(100);
    PORTB = 0x00;
    partirMinuterie(7810);
    do {

    } while(minuterieExpiree == 0 && boutonPoussoir == 0);

    cli();
    if(boutonPoussoir == 1) {
        PORTB = 0x01;
    } else {
        PORTB = 0x02;
    }
}

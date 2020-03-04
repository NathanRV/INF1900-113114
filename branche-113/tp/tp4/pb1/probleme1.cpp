#define F_CPU 8000000 
#define ISR_BLOCK

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

volatile uint8_t etat = 0;

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR (INT0_vect, ISR_BLOCK) {
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    
    // changements d'états tels que ceux de la
    // semaine précédente
    ++etat;
    if(etat == 6) {
        etat = 0;
    }
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) {
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

void ambre() {
    _delay_ms(5);
    PORTB = 0x02;
    _delay_ms(15);
    PORTB = 0x01;   
}

void controlerDEL(uint8_t etatPresent) {
    switch(etatPresent) {
        case 0 : PORTB = 0x01;
        break;
        case 1 : ambre();
        break;
        case 2: PORTB = 0x02;
        break;
        case 3 : PORTB = 0x01;
        break;
        case 4 : PORTB = 0x00;
        break;
        case 5: PORTB = 0x02;
        break;
    }
}

int main() {
    initialisation();
    for(;;) {
        controlerDEL(etat);
    }
    return 0;
}
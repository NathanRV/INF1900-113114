// Travail : TP6 probleme1
// Description : Ce programme modifie l'etat de la lumiere a l'aide d'une 
//               machine a etats controlee par interruption.
// Section # : 3
// Équipe # : 113
// Auteurs : Agnes Sam Yue Chi (1954192), Jefferson Lam (1963528)
// Correcteur : Claudia Onorato, Yoan Gauthier

/****************************
NON INTERRUPTION = 0;
INTERRUPTION = 1;

ETAT PRESENT | A | ETAT SUIVANT | SORTIE Z
E0           | 0 |      E0      |   ETEINT
E0           | 1 |      E1      |   ETEINT
E1           | 0 |      E1      |   COMPTEUR INCREMENTE
E1           | X |      E2      |   COMPTEUR INCREMENTE
E2           | X |      E3      |   VERT POUR 0.5s
E3           | X |      E4      |   ETEINT POUR 2s
E4           | X |      E5      |   CLIGNOTER ROUGE
E5           | X |      E0      |   LUMIERE VERTE 1s

****************************/
#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t ENTREE               = 0x00;
const uint8_t SORTIE               = 0xFF;
const uint8_t VERT                 = 0x02;
const uint8_t ROUGE                = 0x01;
const uint8_t ETEINT               = 0x00;
const uint8_t COMPTEUR_LIMITE      = 120;
const uint8_t COMPTEUR_INCREMENT   = 10;
const double  DELAI_DEUX_SECONDES  = 2000;
const double  DELAI_UNE_SECONDE    = 1000;
const double  DELAI_DEMI_SECONDE   = 500;
const double  DELAI_QUART_SECONDE  = 250;
const double  DELAI_INTERRUPTION   = 30; 

volatile uint8_t compteur = 0;
volatile uint8_t etat     = 0;


ISR (INT0_vect) {
    _delay_ms(DELAI_INTERRUPTION);    
    if(etat == 0 || etat == 1) {
        etat++;
    }
    EIFR |= (1 << INTF0) ;
}

void initialisation(void) {
    cli();
    DDRD = ENTREE;
    DDRB = SORTIE;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

void changerEtatLumiere (void) {
    switch(etat) {
            case 0:
                PORTB = ETEINT;
                break;

            case 1: 
                _delay_ms(DELAI_UNE_SECONDE);
                compteur += COMPTEUR_INCREMENT;
                if(compteur == COMPTEUR_LIMITE) {
                    etat++;
                }
                break;

            case 2:
                PORTB = VERT;
                _delay_ms(DELAI_DEMI_SECONDE);
                etat++;
                break;
            
            case 3:
                PORTB = ETEINT;
                _delay_ms(DELAI_DEUX_SECONDES);
                etat++;
                break;

            case 4:
                for(uint8_t i = 0; i < compteur / 2; ++i) {
                    PORTB = ROUGE;
                    _delay_ms(DELAI_QUART_SECONDE);
                    PORTB = ETEINT;
                    _delay_ms(DELAI_QUART_SECONDE);
                    PORTB = ROUGE;
                    _delay_ms(DELAI_QUART_SECONDE);
                    PORTB = ETEINT;
                    _delay_ms(DELAI_QUART_SECONDE);
                }
                etat++;
                break;

            case 5: 
                PORTB = VERT;
                _delay_ms(DELAI_UNE_SECONDE);
                etat = 0;
                compteur = 0;
                break;

            default : break;
        }
}

int main() {
    initialisation();
    for(;;) {
        changerEtatLumiere();
    }
}
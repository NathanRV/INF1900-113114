
// Travail : TP2 probleme2
// Description : Ce programme fait clignoter la DEL d'une couleur differente a chaque fois qu'on clique le bouton.
// Section # : 3
// Équipe # : 113
// Auteurs : Agnes Sam Yue Chi (1954192), Jefferson Lam (1963528)
// Correcteur : Claudia Onorato, Yoan Gauthier

/*
**********MACHINE DE MEALY - TABLEAU D'ETATS**************************
ETAT PRESENT  |   A    |   ETAT SUIVANT  |  SORTIE Z     
INIT          |   0    |      INIT       |    ROUGE
INIT          |   1    |       E1        |    AMBRE
E1            |   0    |       E1        |    VERT
E1            |   1    |       E2        |    ROUGE
E2            |   0    |       E2        |    ETEINT
E2            |   1    |      INIT       |    VERT
*/


#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>

const int ENTREE = 0x00;
const int SORTIE = 0xFF;
const int SIGNAL2 = 0x04;
const int DELAI_VERT = 5;
const int DELAI_ROUGE = 15;
const int DELAI_DEBOUNCE = 10;
const int VERT = 0x02;
const int ROUGE = 0x01;
const int ETEINTE = 0x00;

enum Etat {
    INIT,
    E1,
    E2
};

/*
Fonction antirebond
return: Un booléen qui évalue si le bouton et encore poussé apres un délai.
*/
bool debounce() {
    if(PIND & SIGNAL2) {
        _delay_ms(DELAI_DEBOUNCE);
        return true;
    }
    return false;
}

void ambre() {
    _delay_ms(DELAI_VERT);
    PORTB = VERT;
    _delay_ms(DELAI_ROUGE);
    PORTB = ROUGE;   
}

int main() {
    
    DDRD = ENTREE;
    DDRB = SORTIE;
    Etat etat = INIT;

    for(;;) {
        switch(etat) {
            case(INIT): 
                PORTB = ROUGE;
                while (debounce()) {
                    ambre();
                    etat = E1; 
                }
                break;
            case(E1):
                PORTB = VERT;
                while (debounce()) {
                    PORTB = ROUGE;
                    etat = E2;
                }
                break;
            case (E2):
                PORTB = ETEINTE;
                while (debounce()) {
                    PORTB = VERT;
                    etat = INIT;
                }                
                break;
            default: break;
        }
    }
}
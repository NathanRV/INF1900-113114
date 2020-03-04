
// Travail : TP2 probleme 1
// Description : Ce programme fait clignoter la DEL apres avoir poussé le bouton 4 fois.
// Section # : 3
// Équipe # : 113
// Auteurs : Agnes Sam Yue Chi (1954192), Jefferson Lam (1963528)
// Correcteur : Claudia Onorato, Yoan Gauthier

/*
**********MACHINE DE MOORE - TABLEAU D'ETATS**************************
ETAT PRESENT  |   A    |   ETAT SUIVANT  |  SORTIE Z     
INIT          |   0    |      INIT       |    0
INIT          |   1    |       B1        |    0
B1            |   0    |       B1        |    0
B1            |   1    |       B2        |    0
B2            |   0    |       B2        |    0
B2            |   1    |       B3        |    0
B3            |   0    |       B3        |    0
B3            |   1    |       B4        |    0
B4            |   0    |       B4        |    0
B4            |   1    |       BON       |    0
BON           |   0    |       BON       |    1
BON           |   1    |      INIT       |    1
*/



#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>

const int ENTREE = 0x00;
const int SORTIE = 0xFF;
const int SIGNAL2 = 0x04;
const int DELAI_VERT = 5;
const int DELAI_ROUGE = 20;
const int DELAI_DEBOUNCE = 10;
const int VERT = 0x02;
const int ROUGE = 0x01;
const int ETEINTE = 0x00;
const int UNE_SECONDE = 1000;  //combien de cyles pour faire 1 seconde a notre frequence?

enum Etat
{
    INIT = 0,
    B1 = 1,
    B2 = 2,
    B3 = 3,
    B4 = 4,
    BON = 5
};

/*
Fonction antirebond
return: Un booléen qui évalue si le bouton et encore poussé apres un délai.
*/
bool debounce() {
    if(PIND & SIGNAL2) {
        _delay_ms(DELAI_DEBOUNCE);
        if(PIND & SIGNAL2) {
            while(PIND & SIGNAL2) {}
            return true;
        }
    }
    return false;
}

void changerEtatLorsqueAppuye(Etat& etatPresent) {
    if(debounce()){
        etatPresent = Etat(etatPresent + 1);
    }
}

int main () {

    DDRD = ENTREE;
    DDRB = SORTIE;
    Etat etat = INIT;
    PORTB = ETEINTE;

    for(;;) {
        switch(etat) {
            case(INIT):
                changerEtatLorsqueAppuye(etat);
                break;
            case(B1):
                changerEtatLorsqueAppuye(etat);
                break;
            case(B2):
                changerEtatLorsqueAppuye(etat);
                break;
            case(B3):
                changerEtatLorsqueAppuye(etat);
                break;
            case(B4):
                changerEtatLorsqueAppuye(etat);
                break;
            case(BON):  
                PORTB = ROUGE;
                _delay_ms(UNE_SECONDE);
                PORTB = ETEINTE;
                etat = INIT;               
                break;
            default: break;  
        }
    }
}
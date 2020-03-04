// Travail : TP6 probleme2
// Description : Ce programme controle la couleur de la DEL selon l'intensite 
//               de la lumiere sur la photoresistance.
// Section # : 3
// Équipe # : 113
// Auteurs : Agnes Sam Yue Chi (1954192), Jefferson Lam (1963528)
// Correcteur : Claudia Onorato, Yoan Gauthier


#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

const uint8_t ENTREE        = 0x00;
const uint8_t SORTIE        = 0xFF;
const uint8_t VERT          = 0x02;
const uint8_t ROUGE         = 0x01;
const uint8_t ETEINT        = 0x00;
const uint8_t LUMIERE_BASSE = 100;
const uint8_t LUMIERE_HAUTE = 230;
const uint8_t DECALAGE_BITS = 2;
const double  DELAI_AMBRE   = 10;

void changerLumiereAmbre() {
    PORTB = ROUGE;
    _delay_ms(DELAI_AMBRE);
    PORTB = VERT;
    _delay_ms(DELAI_AMBRE);
}

void controlerLumiereSelonIntensite(can& convertisseur) {
    uint8_t lectureCapteur = (convertisseur.lecture(0) >> DECALAGE_BITS);
    if(lectureCapteur < LUMIERE_BASSE) {
        PORTB = VERT;
    } 
    else if(lectureCapteur > LUMIERE_HAUTE) {
        PORTB = ROUGE;
    }
    else {
        changerLumiereAmbre();
    }
}

int main() {
    DDRA = ENTREE;
    DDRB = SORTIE;
    can convertisseur;
    for(;;) {
        controlerLumiereSelonIntensite(convertisseur);
    }
}
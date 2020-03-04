#include "controleDEL.h"

void CouleurAmbre () {
    _delay_ms(10);
    PORTB = COULEUR_ROUGE;
    _delay_ms(10);
    PORTB = COULEUR_VERT;
}

void CouleurRouge (uint8_t duree) {
    PORTB = COULEUR_ROUGE;
    _delay_ms(duree);
}

void CouleurVert (uint8_t duree) {
    PORTB = COULEUR_VERT;
    _delay_ms(duree);
}


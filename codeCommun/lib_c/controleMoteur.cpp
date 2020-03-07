#include "controleMoteur.h"


//Fonction permettant d'ajuster l'intensite du
//PWM genere par les interruptions.
//@param in : intensiteGauche et intensiteDroite, une valeur entre 0 et 255 qui 
// represente la frequence a la quelle le PWM sera generee sur la roue gauche ou droite
void partirMoteurs (uint8_t intensiteGauche, uint8_t intensiteDroite) {
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)
    OCR1A = intensiteGauche;
    OCR1B = intensiteDroite;
    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1A |= (1 << WGM10 | 1 << COM1A0 | 1 << COM1A1);
    TCCR1B |= (1 << CS11);
    TCCR1C = 0;
}

//Fonction permettant d'ajuster l'intensite du
//PWM genere par les interruptions à 0.
void arreterMoteur () {
    partirMoteurs(0, 0);
}

//Fonction permettant de donner une direction et une intensité aux deux roues
//@param in : intensite, une valeur entre 0 et 255 qui 
// represente la frequence a la quelle le PWM sera generee sur le moteur
//@param in: direction, la direction dans laquelle la roue va tourner
void dirigerRoues (uint8_t direction, uint8_t intensite) {
    PORTD = direction;
    partirMoteurs(intensite, intensite);
}

//Fonction permettant de donner une direction et une intensité aux deux roues
//@param in : intensiteGauche et intensiteDroite, une valeur entre 0 et 255 qui 
// represente la frequence a la quelle le PWM sera generee sur la roue gauche ou droite
//@param in: direction, la direction dans laquelle la roue va tourner
void tournerRoues (uint8_t direction, uint8_t intensiteGauche, uint8_t intensiteDroite) {
    PORTD = direction;
    partirMoteurs(intensiteGauche, intensiteDroite);
}





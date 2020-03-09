#include "controleMoteur.h"

/**
 * Fonction permettant d'ajuster l'intensite du
 * PWM genere par les interruptions.
 * @param intensiteGauche : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue gauche
 * @param intensiteDroite : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue droite
 * @return void
 */
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

/**
 * Fonction permettant d'ajuster l'intensite du
 * PWM genere par les interruptions à 0.
 * @return void
 */
void arreterMoteur () {
    partirMoteurs(0, 0);
}

/**
 * Fonction permettant de donner une direction et une intensité aux deux roues
 * @param direction: uint8_t, la direction dans laquelle la roue va tourner
 * @param intensite : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur le moteur
 * @return void
 */
void dirigerRoues (uint8_t direction, uint8_t intensite) {
    PORTD = direction;
    partirMoteurs(intensite, intensite);
}

/**
 * Fonction permettant de donner une direction et une intensité aux deux roues
 * @param direction: uint8_t, la direction dans laquelle la roue va tourner
 * @param intensiteGauche : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue gauche
 * @param intensiteDroite : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue droite
 * @return void
 */
void tournerRoues (uint8_t direction, uint8_t intensiteGauche, uint8_t intensiteDroite) {
    PORTD = direction;
    partirMoteurs(intensiteGauche, intensiteDroite);
}




/** 
 * Fonction permettant d'ajuster le pourcentage du PWM sur la PIND
 * 
 * @param pourcentage : uint8_t, pourcentage de 0 à 100 du PWM
 * @return void
*/
void ajusterPWM ( uint8_t pourcentage ) {
    initialiserDDRD(SORTIE);
    TCNT1 = 0; //compteur à 0

	//f=fréquence, N=facteur de prescaler
	//fOCnA=fclk/2N(1+OCRnX)

    if(pourcentage­>100){   //verification du pourcentage
        pourcentage=100;
    }

	//Formule de transfert du pourcentage à valeur numérique
	uint8_t maxValueCounter = 0xFFFF; //65 535
	uint8_t maxValuePercent = round(maxValueCounter / 100); //655
	uint8_t value = maxValuePercent * percent;

	//Valeur de comparaison
	OCR1A = value ;
	OCR1B = value ;

	//Timer/Counter Control Register 1 A (TCCR1A)
	TCCR1A |= (1<<COM1A1) |(1<<COM1B1) ; 
	//OC1A OC1B mis à 0 sur comparaison, mis à 1 lorsque BOTTOM
	//PWM rapide

	//Timer/Counter Control Register 1 B (TCCR1B)
	//Facteur prescaler
	TCCR1B |= (1 << CS11);
	//Divisé par 8 (CS11)
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << WGM11);
	//mode PWM rapide (16 bits) où TOP=ICRn
	ICR1 = maxValueCounter;

	TCCR1C = 0;
}
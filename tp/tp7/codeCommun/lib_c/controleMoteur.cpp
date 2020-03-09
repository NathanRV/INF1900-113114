/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  controleMoteur.cpp
*/

#include "controleMoteur.h"

/** 
 * Fonction permettant d'ajuster le pourcentage du PWM sur la PIND
 * 
 * @param pourcentageDroite : uint8_t, pourcentage de 0 à 100 du PWM
 * @param pourcentageGauche : uint8_t, pourcentage de 0 à 100 du PWM
 * @return void
*/
void ajusterPWM( uint8_t pourcentageDroite, uint8_t pourcentageGauche ) {
    initialiserDDRD(SORTIE);
    TCNT1 = 0; //compteur à 0

	//f=fréquence, N=facteur de prescaler
	//fOCnA=fclk/2N(1+OCRnX)

    if(pourcentageDroite>100){   //verification du pourcentage
        pourcentageDroite=100;
    }
	if(pourcentageGauche>100){
		pourcentageGauche=100;
	}

	//Formule de transfert du pourcentage à valeur numérique
	uint16_t maxValeurCompteur = 0xFFFF; //65 535
	uint8_t maxValeurPourcent = round(maxValeurCompteur / 100); //655
	uint16_t valeurDroite = maxValeurPourcent * pourcentageDroite;
	uint16_t valeurGauche = maxValeurPourcent * pourcentageGauche;

	//Valeur de comparaison
	OCR1A = valeurGauche;
	OCR1B = valeurDroite ;

	//Timer/Counter Control Register 1 A (TCCR1A)
	TCCR1A |= (1<<COM1A1) |(1<<COM1B1) ; 
	//OC1A OC1B mis à 0 sur comparaison, mis à 1 lorsque BOTTOM
	//PWM rapide

	//Timer/Counter Control Register 1 B (TCCR1B)
	//Facteur prescaler
	TCCR1B |= (1 << CS11);
	//Divisé par 8 (CS11)
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << WGM11);
	//mode PWM rapide (16 bits) où TOP=ICR1
	ICR1 = maxValeurCompteur;

	TCCR1C = 0;
}

/**
 * Fonction permettant d'ajuster l'intensite du
 * PWM genere par les interruptions à 0.
 * @return void
 */
void arreterMoteur () {
    ajusterPWM(0, 0);
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
    ajusterPWM(intensite, intensite);
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
    ajusterPWM(intensiteGauche, intensiteDroite);
}

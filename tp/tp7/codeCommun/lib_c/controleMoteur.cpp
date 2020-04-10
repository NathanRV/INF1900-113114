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
 * @param pourcentageGauche : int8_t, pourcentage de -100 à 100 du PWM
 * @param pourcentageDroite : int8_t, pourcentage de -100 à 100 du PWM
 * @return void
*/
void ajusterPWM( int8_t pourcentageGauche, int8_t pourcentageDroite ) {
    initialiserDDRD(SORTIE);

	TCNT1 = 0; //compteur à 0
	
	PORTD = 0; //Effacer PORTD

	//Direction gauche
	if(pourcentageGauche < 0){
		PORTD |= RECULERGAUCHE;
		pourcentageGauche = -pourcentageGauche;
	}
	else
	{
		PORTD |= AVANCERGAUCHE;
	}

	//Direction droite
	if(pourcentageDroite < 0){
		PORTD |= RECULERDROITE;
		pourcentageDroite = -pourcentageDroite;
	}
	else
	{
		PORTD |= AVANCERDROITE;
	}

	//f=fréquence, N=facteur de prescaler
	//fOCnA=fclk/2N(1+OCRnX)

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)

    if(pourcentageDroite>99){   //verification du pourcentage
        pourcentageDroite=99;
    }
	if(pourcentageGauche>99){
		pourcentageGauche=99;
	}

    //Formule de transfert du pourcentage à valeur numérique
	uint8_t maxValeurCompteur = 0xFF; //255
	uint16_t valeurDroite = maxValeurCompteur * pourcentageDroite;
	uint16_t valeurGauche = maxValeurCompteur * pourcentageGauche;
    valeurDroite = round(valeurDroite / 100);
    valeurGauche = round(valeurGauche / 100);

    OCR1A = valeurDroite; 
    //Output compare Register 1A correspond à D5 (OC1A)
    
    OCR1B = valeurGauche;
    //Output compare Register 1B correspond à D4 (OC1B)
    
    // division d'horloge par 8 - implique une frequence de PWM fixe

    //Voir p.123 & section 16.10.4
    TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1); //Table 16-4.
    //  COM1A1&COM1B1:Clear OCnA/OCnB on Compare Match when up-counting. 
    //  Set OCnA/OCnB on Compare Match when downcounting.
    //  WGM10:PWM, phase correct, 8-bit
    TCCR1B |= (1 << CS11); //prescaler 8

    TCCR1C = 0; 
}

/**
 * Fonction permettant d'arreter le comptage
 * @return void
*/
void arretPWM(){
    OCR1A = 0; 
    OCR1B = 0;
    TCCR1A = 0;
}

/**
 * Fonction permettant d'ajuster l'intensite du
 * PWM genere par les interruptions à 0.
 * @return void
 */
void arreterMoteur () {
    ajusterPWM(0, 0);
    arretPWM();
}



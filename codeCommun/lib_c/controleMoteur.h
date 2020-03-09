#ifndef CONTROLE_MOTEUR_H
#define CONTROLE_MOTEUR_H

#include "constantes.h"
#include "initialisation.h"
#include <avr/interrupt.h>

/** 
 * Fonction permettant d'ajuster le pourcentage du PWM sur la PIND
 * 
 * @param pourcentage : uint8_t, pourcentage de 0 à 100 du PWM
 * @return void
*/
void ajusterPWM ( uint8_t pourcentageDroite, uint8_t pourcentageGauche );

/**
 * Fonction permettant d'ajuster l'intensite du
 * PWM genere par les interruptions.
 * @param intensiteGauche : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue gauche
 * @param intensiteDroite : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue droite
 * @return void
 */
void partirMoteurs (uint8_t intensite);

/**
 * Fonction permettant d'ajuster l'intensite du
 * PWM genere par les interruptions à 0.
 * @return void
 */
void arreterMoteur ();

/**
 * Fonction permettant de donner une direction et une intensité aux deux roues
 * @param direction: uint8_t, la direction dans laquelle la roue va tourner
 * @param intensite : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur le moteur
 * @return void
 */
void dirigerRoues (uint8_t direction, uint8_t intensite);

/**
 * Fonction permettant de donner une direction et une intensité aux deux roues
 * @param direction: uint8_t, la direction dans laquelle la roue va tourner
 * @param intensiteGauche : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue gauche
 * @param intensiteDroite : uint8_t, une valeur entre 0 et 255 qui 
 * represente la frequence a la quelle le PWM sera generee sur la roue droite
 * @return void
 */
void tournerRoues (uint8_t direction, uint8_t intensiteGauche, uint8_t intensiteDroite);


#endif //CONTROLE_MOTEUR_H
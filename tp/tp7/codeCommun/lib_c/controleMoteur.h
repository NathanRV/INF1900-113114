/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  controleMoteur.h
*/

#ifndef CONTROLE_MOTEUR_H
#define CONTROLE_MOTEUR_H

#include "constantes.h"
#include "initialisation.h"

/** 
 * Fonction permettant d'ajuster le pourcentage du PWM sur la PIND
 * 
 * @param pourcentageDroite : int8_t, pourcentage de -100 à 100 du PWM
 * @param pourcentageGauche : int8_t, pourcentage de -100 à 100 du PWM
 * @return void
*/
void ajusterPWM ( int8_t pourcentageDroite, int8_t pourcentageGauche );

/**
 * Fonction permettant d'ajuster l'intensite du
 * PWM genere par les interruptions à 0.
 * @return void
 */
void arreterMoteur ();

#endif //CONTROLE_MOTEUR_H
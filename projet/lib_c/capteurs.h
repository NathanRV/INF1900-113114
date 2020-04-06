/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  capteurs.h
*/

#include "can.h"
#include "controleDEL.h"

/**
 * Utilise le capteur de photoresistance afin de détecter
 * les variations d'intensite lumineuse. Ambre lorsque intensité
 * entre seuil minimum et maximum.
 * 
 * @param lumiereBasse couleur de la DEL lors du seuil minimum (COULEUR_*)
 * @param lumiereHaute couleur de la DEL lors du seuil maximum (COULEUR_*)
 * @return void
 */
void controlerLumiereSelonIntensite(uint8_t lumiereBasse, uint8_t lumiereHaute);

/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  controleDEL.h
*/

#include "constantes.h"
#include "delay.h"

/**
 * Permet à la DEL de prendre la couleur ambre
 * 
 * @param duree Duree (en ms) dactivation de la lumiere
 * @return void
 */
void couleurAmbre(uint16_t duree);

/**
 * Permet à la DEL de prendre la couleur verte
 * 
 * @param duree Duree (en ms) d'activation de la lumiere
 * @return void
 */
void couleurVert(uint16_t duree);

/**
 * Permet à la DEL de prendre la couleur rouge
 * 
 * @param duree Duree (en ms) d'activation de la lumiere
 * @return void
 */
void couleurRouge(uint16_t duree);

/**
 * Force la DEL à être éteinte
 * 
 * @param none
 * @return void
 */
void couleurEteint();

/**
 * Permet l'atténuation de la DEL
 * 
 * @param periode La période d'atténuation
 * @param couleurLumiere La couleur que va prendre la DEL 
 * @param dureeAttenuation Le temps(ms) que prend la DEL pour atténuer complètement
 * @return void
 */
void attenuerDEL(uint16_t period, uint8_t couleurLumiere, uint16_t dureeAttenuation);

/**
 * Permet à la DEL de clignoter selon un rythme spécifié 
 * 
 * @param couleurLumiere La couleur que va prendre la DEL
 * @param dureeClignotement La duree en ms de chaque clignotement (50/50)
 * @param repetitions Nombre de clignotements
 * @return void
 */
void clignoterDEL(uint8_t couleurLumiere, uint16_t dureeClignotement, uint8_t repetitions);

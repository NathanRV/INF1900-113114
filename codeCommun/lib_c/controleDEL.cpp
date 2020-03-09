#include "controleDEL.h"

/**
 * Permet à la DEL de prendre la couleur ambre
 * 
 * @param duree Duree (en ms) dactivation de la lumiere
 * @return void
 */

void couleurAmbre(uint16_t duree)
{
    uint16_t repetitions=duree/20;  //2*10 ms de delai
    for (uint16_t i = 0; i < repetitions; i++)
    {
        PORTB = COULEUR_ROUGE;
        attendre_ms(10);
        PORTB = COULEUR_VERT;
        attendre_ms(10);
    }
}

/**
 * Permet à la DEL de prendre la couleur rouge
 * 
 * @param duree Duree (en ms) d'activation de la lumiere
 * @return void
 */

void couleurRouge(uint16_t duree)
{
    PORTB = COULEUR_ROUGE;
    attendre_ms(duree);
}

/**
 * Permet à la DEL de prendre la couleur verte
 * 
 * @param duree Duree (en ms) d'activation de la lumiere
 * @return void
 */

void couleurVert(uint16_t duree)
{
    PORTB = COULEUR_VERT;
    attendre_ms(duree);
}

/**
 * Force la DEL à être éteinte
 * 
 * @param none
 * @return void
 */

void couleurEteint()
{
    PORTB = COULEUR_AUCUNE;
}

/**
 * Permet l'atténuation de la DEL
 * 
 * @param periode La période d'atténuation
 * @param couleurLumiere La couleur que va prendre la DEL 
 * @param dureeAttenuation Le temps(ms) que prend la DEL pour atténuer complètement
 * @return void
 */

void attenuerDEL(uint16_t periode, uint8_t couleurLumiere, uint16_t dureeAttenuation)
{
    for (uint8_t i = 0; i < dureeAttenuation; ++i)
    {
        uint8_t intensiteDecrementation = floor(i * periode / dureeAttenuation);
        PORTB = couleurLumiere;
        attendre_ms(periode - intensiteDecrementation);
        PORTB = COULEUR_AUCUNE;
        attendre_ms(intensiteDecrementation);
    }
}

/**
 * Permet à la DEL de clignoter selon un rythme spécifié 
 * 
 * @param couleurLumiere La couleur que va prendre la DEL
 * @param dureeClignotement La duree en ms de chaque clignotement (50/50)
 * @param repetitions Nombre de clignotements
 * @return void
 */

void clignoterDEL(uint8_t couleurLumiere, uint16_t dureeClignotement, uint8_t repetitions)
{
    for (uint8_t i = 0; i < repetitions; ++i)
    {
        PORTB = couleurLumiere;
        attendre_ms(dureeClignotement);
        PORTB = COULEUR_AUCUNE;
        attendre_ms(dureeClignotement);
    }
}
#include "controleDEL.h"

/**
 * Permet à la DEL de prendre la couleur ambre
 * 
 * @param none
 * @return void
 */

void couleurAmbre() {
    PORTB = COULEUR_ROUGE;
    _delay_ms(10);
    PORTB = COULEUR_VERT;
    _delay_ms(10);
}

/**
 * Permet à la DEL de prendre la couleur rouge
 * 
 * @param duree Duree de temps d'activation de la lumiere
 * @return void
 */

void couleurRouge(uint8_t duree) {
    PORTB = COULEUR_ROUGE;
    attendre(duree);
}

/**
 * Permet à la DEL de prendre la couleur verte
 * 
 * @param duree Duree de temps d'activation de la lumiere
 * @return void
 */

void couleurVert(uint8_t duree) {
    PORTB = COULEUR_VERT;
    attendre(duree);
}

/**
 * Force la DEL à être éteinte
 * 
 * @param none
 * @return void
 */

void couleurEteint() {
    PORTB = LUMIERE_ETEINTE;
}

/**
 * Permet l'atténuation de la DEL
 * 
 * @param periode La période d'atténuation
 * @param couleurLumiere La couleur que va prendre la DEL 
 * @param dureeAttenuation Le temps que prend la DEL pour atténuer complètement
 * @return void
 */

void attenuerDEL(uint8_t periode, uint8_t couleurLumiere, uint8_t dureeAttenuation) {
    for (uint8_t i = 0; i < dureeAttenuation; ++i) {
        uint8_t intensiteDecrementation = floor(i * periode / dureeAttenuation);
        PORTB = couleurLumiere;
        attendre(periode - intensiteDecrementation);
        PORTB = LUMIERE_ETEINTE;
        attendre(intensiteDecrementation);
    }
}

/**
 * Permet à la DEL de clignoter selon un rythme spécifié 
 * 
 * @param couleurLumiere La couleur que va prendre la DEL
 * @param dureeClignotement La duree en temps de chaque clignotement
 * @param repetitions Nombre de clignotements
 * @return void
 */

void clignoterDEL(uint8_t couleurLumiere, uint8_t dureeClignotement, uint8_t repetitions) {
    for (uint8_t i = 0; i < repetitions; ++i) {
        PORTB = couleurLumiere;
        attendre(dureeClignotement);
        PORTB = LUMIERE_ETEINTE;
        attendre(dureeClignotement);
    }
}
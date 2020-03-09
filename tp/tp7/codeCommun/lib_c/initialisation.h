/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  initialisation.h
*/

#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "constantes.h"

/**
 * Initialise la direction du port A
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRA(uint8_t etat);

/**
 * Initialise la direction du port B
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRB(uint8_t etat);

/**
 * Initialise la direction du port C
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRC(uint8_t etat);

/**
 * Initialise la direction du port D
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRD(uint8_t etat);

/**
 * Initialise la direction des ports A, B, C et D
 * @param etatA, etatB, etatC, etatD (ENTREE ou SORTIE)
 * @return void
 */
void initialiserDDR(uint8_t etatA, uint8_t etatB, uint8_t etatC, uint8_t etatD);

/**
 * Initialise l'UART dans le microcontroleur
 * @param void
 * return void
 */
void initialisationUART(void);

/**
 * Initialise la direction des ports A, B, C et D avec une routine d'interruption
 * @param etatA, etatB, etatC, etatD (ENTREE ou SORTIE)
 * @return void
 */
void initialisationInteruption(uint8_t etatA, uint8_t etatB, uint8_t etatC, uint8_t etatD);

#endif //INITIALISATION_H
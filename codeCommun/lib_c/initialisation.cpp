#include "initialisation.h"

/**
 * Initialise la direction du port A
 * @param etat 0x00 pour entree, 0xFF pour sortie
 * @return void
 */
void initialiserDDRA(uint8_t etat) {
    DDRA = etat;
}

/**
 * Initialise la direction du port B
 * @param etat 0x00 pour entree, 0xFF pour sortie
 * @return void
 */
void initialiserDDRB(uint8_t etat) {
    DDRB = etat;
}

/**
 * Initialise la direction du port C
 * @param etat 0x00 pour entree, 0xFF pour sortie
 * @return void
 */
void initialiserDDRC(uint8_t etat) {
    DDRC = etat;
}

/**
 * Initialise la direction du port D
 * @param etat 0x00 pour entree, 0xFF pour sortie
 * @return void
 */
void initialiserDDRD(uint8_t etat) {
    DDRD = etat;
}

/**
 * Initialise la direction des ports A, B, C et C
 * @param etatA, etatB, etatC, etatD 0x00 pour entree, 0xFF pour sortie
 * @return void
 */
void initialiserDDR(uint8_t etatA, uint8_t etatB, uint8_t etatC, uint8_t etatD) {
    DDRA = etatA;
    DDRB = etatB;
    DDRC = etatC;
    DDRD = etatD;
}
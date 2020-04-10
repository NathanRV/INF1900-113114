/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  initialisation.cpp
*/

#include "initialisation.h"

/**
 * Initialise la direction du port A
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRA(uint8_t etat) {
    DDRA = 0;
    DDRA = etat;
}

/**
 * Initialise la direction du port B
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRB(uint8_t etat) {
    DDRB = 0;
    DDRB = etat;
}

/**
 * Initialise la direction du port C
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRC(uint8_t etat) {
    DDRC = 0;
    DDRC = etat;
}

/**
 * Initialise la direction du port D
 * @param etat ENTREE ou SORTIE
 * @return void
 */
void initialiserDDRD(uint8_t etat) {
    DDRD = 0;
    DDRD = etat;
}

/**
 * Initialise la direction des ports A, B, C et D
 * @param etatA, etatB, etatC, etatD (ENTREE ou SORTIE)
 * @return void
 */
void initialiserDDR(uint8_t etatA, uint8_t etatB, uint8_t etatC, uint8_t etatD) {
    initialiserDDRA(etatA);
    initialiserDDRB(etatB);
    initialiserDDRC(etatC);
    initialiserDDRD(etatD);
}

/**
 * Initialise l'UART dans le microcontroleur
 * @param void
 * return void
 */
void initialisationUART(void) {

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications

    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A =0;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); 
    //modifie  receive,transfer enabled

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C |= (1 << UCSZ11) | (1 << UCSZ10); //char size
}

/**
 * Initialise la direction des ports A, B, C et D avec une routine d'interruption
 * @param etatA, etatB, etatC, etatD (ENTREE ou SORTIE)
 * @return void
 */
void initialisationInterruption(uint8_t etatA, uint8_t etatB, uint8_t etatC, uint8_t etatD) {

    /*cli est une routine qui bloque toutes les interruptions.
    Il serait bien mauvais d'être interrompu alors que
    le microcontroleur n'est pas prêt...*/
    cli();

    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    initialiserDDR(etatA, etatB, etatC, etatD);

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    //EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= 0b01;

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}
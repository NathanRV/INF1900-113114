/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  interactionUART.h
*/

#include "memoire_24.h"
#include "delay.h"
#include "constantes.h"

/**
 * Transmet donnee à l'ordinateur via UART
 * @param donnee : uint8_t donnee à transmettre via UART
 * @return void
 */
void transmissionUART(uint8_t donnee); 


/**
 * Écrit message en memoire
 * @param memoire : instance de Memoire24CXXX*
 * @param message : message à écrire (char [])
 * @param adresse : adresse memoire où écrire (par défaut 0x00)
 * @return void
 */
void ecrireMessageMemoire(Memoire24CXXX* memoire, char* message, const uint16_t adresse=0x00);
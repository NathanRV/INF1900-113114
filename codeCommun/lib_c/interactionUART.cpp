/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  interactionUART.cpp
*/

#include "interactionUART.h"

/**
 * Transmet donnee à l'ordinateur via UART
 * @param donnee : uint8_t donnee à transmettre via UART
 * @return void
 */
void transmissionUART(uint8_t donnee) {
    
    /* Attendre queue de transmission vide */
    while (!(UCSR0A & (1 << UDRE0))) {};

    /* Copier 9ieme bit (s'il y en a un) à TXB8 */
    UCSR0B &= ~(1 << TXB80);

    if (donnee & 0x0100){
        UCSR0B |= (1 << TXB80);
    }
    /* Place donnee dans queue de transmission, transmission débute */
    UDR0 = donnee;
}

/**
 * Écrit message en memoire
 * @param memoire : instance de Memoire24CXXX*
 * @param message : message à écrire (char [])
 * @param adresse : adresse memoire où écrire (par défaut 0x00)
 * @return void
 */
void ecrireMessageMemoire(Memoire24CXXX* memoire, char* message,const uint16_t adresse) {
    memoire->ecriture(adresse,(uint8_t*) message, sizeof(message));
    attendre_ms(5);
}
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
void ecrireMessageMemoire(Memoire24CXXX* memoire, char message [], const uint16_t adresse=0x00);
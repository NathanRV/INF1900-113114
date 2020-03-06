#ifndef INITIALISATION_H
#define INITIALISATION_H

#include <avr/io.h>
#include <util/delay.h>


void initialiserDDRA(uint8_t etat);
void initialiserDDRB(uint8_t etat);
void initialiserDDRC(uint8_t etat);
void initialiserDDRD(uint8_t etat);
void initialiserDDR(uint8_t etatA, uint8_t etatB, uint8_t etatC, uint8_t etatD);


#endif //INITIALISATION_H
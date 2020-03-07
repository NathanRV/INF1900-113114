#ifndef CONTROLE_MOTEUR_H
#define CONTROLE_MOTEUR_H

#include "constantes.h"
#include <avr/interrupt.h>

void partirMoteurs (uint8_t intensite);
void arreterMoteur ();
void dirigerRoues (uint8_t direction, uint8_t intensite);
void tournerRoues (uint8_t direction, uint8_t intensiteGauche, uint8_t intensiteDroite);


#endif //CONTROLE_MOTEUR_H
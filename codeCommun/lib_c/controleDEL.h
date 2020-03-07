#include "constantes.h"
#include "delay.h"

void couleurAmbre();

void couleurVert(uint8_t duree);

void couleurRouge(uint8_t duree);

void couleurEteint();

void attenuerDEL(uint8_t period, uint8_t couleurLumiere, uint8_t dureeAttenuation);

void clignoterDEL(uint8_t couleur, uint8_t duree, uint8_t repetitions);
#include "controleDEL.h"
#include "controleMoteur.h"
#include "capteurs.h"
#include "can.h"
#include "initialisation.h"
#include "constantes.h"
#include "delay.h"
#include "interactionUART.h"
#include "antirebond.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

void afficheTrait();

void activerAfficheur();

void changerAfficheur();

void affichage(uint8_t gauche, uint8_t droite);

void minuterieAfficheur(uint8_t valeur);

void affiche(uint8_t chiffre);
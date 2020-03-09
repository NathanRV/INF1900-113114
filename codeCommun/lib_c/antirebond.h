#ifndef ANTIREBOND_H
#define ANTIREBOND_H

#include "constantes.h"
#include <avr/io.h> 

/**
 * Fonction antirebond
 * @return Un booléen qui évalue si le bouton est encore enfoncé apres un délai.
 */
bool boutonAntiRebond(void);

#endif //ANTIREBOND_H
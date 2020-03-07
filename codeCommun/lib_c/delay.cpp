#include "delay.h"

/**
 * Permet un delai à l'état selon le temps passeé en paramètres
 * Cette fonction rend le passage de parametres pour les delais
 * 
 * @param millisecondes la duree de délai en ms
 * @return void
 */
void attendre (int millisecondes) {
    for (int i = 0; i < millisecondes; ++i) {
        _delay_ms(1);
    }
}
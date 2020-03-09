#include "delay.h"

/**
 * Permet un delai à l'état selon le temps passé en paramètres
 * Cette fonction rend le passage de parametres pour les delais
 * 
 * @param millisecondes la duree de délai en ms
 * @return void
 */
void attendre_ms(uint16_t millisecondes) {
    for(uint16_t i = 0; i < millisecondes; i++) { //delai x ms
        uint16_t repetition = (F_CPU / 1000) / 4;
        _delay_loop_2(repetition); //4 cycle de CPU * F_CPU/1000/4=F_CPU/1000 cycle
        //F_CPU/1000*1000Ms=F_CPU instructions = 1sec
    }
}
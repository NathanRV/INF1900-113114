#include "antirebond.h"
 

const double DELAI_REBOND_MS = 10; 

/**
 * Fonction antirebond
 * @return Un booléen qui évalue si le bouton est encore enfoncé apres un délai.
 */
bool boutonAntiRebond(void) {
    if(EST_APPUYE) {
        _delay_ms(DELAI_REBOND_MS);
        if(EST_APPUYE){
            return true;
        }
    }
    return false;
}
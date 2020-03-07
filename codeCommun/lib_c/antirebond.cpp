#include "antirebond.h"

const double DELAI_REBOND_MS = 10; 

/**
 * Fonction antirebond
 * @return Un booléen qui évalue si le bouton et encore poussé apres un délai.
 */
bool boutonSiAppuye(void) {
    if(EST_APPUYE) {
        _delay_ms(DELAI_REBOND_MS);
        return true;
    }
    return false;
}
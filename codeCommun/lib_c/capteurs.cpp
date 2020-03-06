#include "capteurs.h"

void controlerLumiereSelonIntensite(can& convertisseur, uint8_t lumiereBasse, uint8_t lumiereHaute) {
    uint8_t lectureCapteur = (convertisseur.lecture(0) >> DECALAGE_2BIT);
    if(lectureCapteur > SEUIL_LUMIERE_HAUTE) {
        PORTB = lumiereHaute;
    } 
    else if(lectureCapteur < SEUIL_LUMIERE_BASSE) {
        PORTB = lumiereBasse;
    }
    else {
        couleurAmbre();
    }
}

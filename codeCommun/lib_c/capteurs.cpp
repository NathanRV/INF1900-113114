#include "capteurs.h"

/**
 * Utilise le capteur de photoresistance afin de détecter
 * les variations d'intensite lumineuse
 * 
 * @param convertisseur objet de type can permettant la conversion 
 *                      analogique/numerique
 * @param lumiereBasse couleur de la DEL lors du seuil minimum
 * @param lumiereHaute couleur de la DEL lors du seuil maximum
 * @return void
 */

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

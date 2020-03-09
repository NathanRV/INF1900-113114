#include "capteurs.h"

/**
 * Utilise le capteur de photoresistance afin de détecter
 * les variations d'intensite lumineuse. Ambre lorsque intensité
 * entre seuil minimum et maximum.
 * 
 * @param lumiereBasse couleur de la DEL lors du seuil minimum (COULEUR_*)
 * @param lumiereHaute couleur de la DEL lors du seuil maximum (COULEUR_*)
 * @return void
 */

void controlerLumiereSelonIntensite(uint8_t lumiereBasse, uint8_t lumiereHaute) {
    can convertisseur;
    uint8_t lectureCapteur = (convertisseur.lecture(0) >> DECALAGE_2BIT);
    for(;;){
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
}

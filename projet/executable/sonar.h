#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "initialisation.h"
#include "delay.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

class Sonar
{
public:
    Sonar() : disp(&DDRB, &PORTB)
    {
        //set pre-scaler
        TCCR1B |= (1 << CS11);
    }

    /*
    * Methode qui envoie un signal "trigger" pour enclencher un signal au sonar
    * qui calcule la distance entre le sonar et l'objet
    * 
    * @param in: sonarPort le pin spécifique du port A connecté au sonar voulu
    * @param out: la distance entre le sonar et l'objet
    */
    float calculerDistance(uint8_t sonarPort);

    /**
     * Methode qui calculer les 3 distances et
     * met a jour les attributs de l'objet
     */
    void calculerDistances();

    /*
    * Méthode qui permet l'activation des trois sonars et qui met a jour les 
    * les distances detectes 
    */
    void detecterObjets();

    /*
    * Affiche les trois mesures de distances
    */
    void afficherMesures();

    /**
     * Accesseurs de distances
     */
    float getDistance1();
    float getDistance2();
    float getDistance3();

private:
    float distanceSonar1, distanceSonar2, distanceSonar3;
    LCM disp;
};

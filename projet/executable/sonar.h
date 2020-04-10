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
    * @param in:
    */
    void calculerDistance(uint8_t sonarPort);

    /*
    * Méthode qui permet d'activer tous les trois sonars
    *  
    * 
    */
    void detecterObjets();

    /*
    * Affiche les trois mesures de distances
    * 
    * 
    */
    void afficherMesures();

private:
    float distanceSonar1, distanceSonar2, distanceSonar3;
    LCM disp;
};

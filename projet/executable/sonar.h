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
    Sonar(LCM *display);

    /*
    * Methode qui envoie un signal "trigger" pour enclencher un signal au sonar
    * qui calcule la distance entre le sonar et l'objet
    * 
    * @param in: sonarPort le pin spécifique du port A connecté au sonar voulu
    * @param out: la distance entre le sonar et l'objet
    */
    float calculerDistance(uint8_t sonarPort);

    /*
    * Méthode qui permet l'activation des trois sonars et qui met a jour les 
    * les distances detectes 
    */
    void detecterObjets();

    /*
    * Affiche les trois mesures de distances
    */
    void afficherMesures();

private:
    float distanceSonar1, distanceSonar2, distanceSonar3;
    LCM *disp;
};

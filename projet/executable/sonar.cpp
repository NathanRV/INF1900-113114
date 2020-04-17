/*
    Date:       11-04-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  sonar.cpp
*/

#include "sonar.h"

float Sonar::calculerDistance(uint8_t sonarPort)
{
    float count = 0;
    
    PORTB |= 0x01; //Activer Trigger (PINB0)
    attendre_ms(10);
    PORTB &= ~(1 << PORTB0);

    TCNT1 = 0;

    while (!(PINA & (1 << sonarPort)) && TCNT1 < LIMITE_COMPTEUR)
        ;

    TCNT1 = 0;

    while ((PINA & (1 << sonarPort)) && TCNT1 < LIMITE_COMPTEUR)
        ;

    count = TCNT1;
    float distance = count / FACTEUR_CONVERSION;
    return distance;

}

void Sonar::calculerDistances(){
    distanceSonar1 = calculerDistance(PINA0);
    distanceSonar2 = calculerDistance(PINA1);
    distanceSonar3 = calculerDistance(PINA2);
}

void Sonar::detecterObjets() {
    calculerDistances();
    afficherMesures();
}

void Sonar::afficherMesures() {
    char sonarOutput1[10], sonarOutput2[10], sonarOutput3[10];
    dtostrf(distanceSonar1, LARGEUR_NOMBRE, PRECISION_NOMBRE, sonarOutput1);
    dtostrf(distanceSonar2, LARGEUR_NOMBRE, PRECISION_NOMBRE, sonarOutput2);
    dtostrf(distanceSonar3, LARGEUR_NOMBRE, PRECISION_NOMBRE, sonarOutput3);
    disp.write(sonarOutput1, POSITION_SONAR1, false);
    disp.put('m');
    disp.write(sonarOutput2, POSITION_SONAR2, false);
    disp.put('m');
    disp.write(sonarOutput3, POSITION_SONAR3, false);
    disp.put('m');

    if (distanceSonar1 < DISTANCE_DNGR) {
        disp.write("DNGR", LCM_FW_HALF_CH, false);
    } else if (distanceSonar1 >= DISTANCE_DNGR && distanceSonar1 < DISTANCE_OK) {
        disp.write("ATTN", LCM_FW_HALF_CH, false);
    } else {
        disp.write(" OK ", LCM_FW_HALF_CH, false);
    }

    if (distanceSonar2 < DISTANCE_DNGR) {
        disp.write("DNGR", LCM_FW_HALF_CH + POSITION_SONAR2, false);
    } else if (distanceSonar2 >= DISTANCE_DNGR && distanceSonar2 < DISTANCE_OK) {
        disp.write("ATTN", LCM_FW_HALF_CH + POSITION_SONAR2, false);
    } else {
        disp.write(" OK ", LCM_FW_HALF_CH + POSITION_SONAR2, false);
    }

    if (distanceSonar3 < DISTANCE_DNGR) {
        disp.write("DNGR", LCM_FW_HALF_CH + POSITION_SONAR3, false);
    } else if (distanceSonar3 >= DISTANCE_DNGR && distanceSonar3 < DISTANCE_OK) {
        disp.write("ATTN", LCM_FW_HALF_CH + POSITION_SONAR3, false);
    } else {
        disp.write(" OK ", LCM_FW_HALF_CH + POSITION_SONAR3, false);
    }

}

/**
 * Accesseurs de distances
 */
float Sonar::getDistance1(){
    return distanceSonar1;
}
float Sonar::getDistance2(){
    return distanceSonar2;
}
float Sonar::getDistance3(){
    return distanceSonar3;
}
#include "sonar.h"

float Sonar::calculerDistance(uint8_t sonarPort)
{
    float count = 0;
    
    PORTB |= 0x01; //Activer Trigger (PINB0)
    attendre_ms(10);
    PORTB &= ~(1 << PORTB0);

    TCNT1 = 0;

    while (!(PINA & (1 << sonarPort)) && TCNT1 < 58800)
        ;

    TCNT1 = 0;

    while ((PINA & (1 << sonarPort)) && TCNT1 < 58800)
        ;

    count = TCNT1;
    float distance = count / 5800;
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
    dtostrf(distanceSonar1, 3, 1, sonarOutput1);
    dtostrf(distanceSonar2, 3, 1, sonarOutput2);
    dtostrf(distanceSonar3, 3, 1, sonarOutput3);
    disp.write(sonarOutput1, 0, false);
    disp.put('m');
    disp.write(sonarOutput2, 6, false);
    disp.put('m');
    disp.write(sonarOutput3, 12, false);
    disp.put('m');

    if (distanceSonar1 < 1) {
        disp.write("DNGR", LCM_FW_HALF_CH, false);
    } else if (distanceSonar1 >= 1 && distanceSonar1 < 3) {
        disp.write("ATTN", LCM_FW_HALF_CH, false);
    } else {
        disp.write(" OK ", LCM_FW_HALF_CH, false);
    }

    if (distanceSonar2 < 1) {
        disp.write("DNGR", LCM_FW_HALF_CH + 6, false);
    } else if (distanceSonar2 >= 1 && distanceSonar2 < 3) {
        disp.write("ATTN", LCM_FW_HALF_CH + 6, false);
    } else {
        disp.write(" OK ", LCM_FW_HALF_CH + 6, false);
    }

    if (distanceSonar3 < 1) {
        disp.write("DNGR", LCM_FW_HALF_CH + 12, false);
    } else if (distanceSonar3 >= 1 && distanceSonar3 < 3) {
        disp.write("ATTN", LCM_FW_HALF_CH + 12, false);
    } else {
        disp.write(" OK ", LCM_FW_HALF_CH + 12, false);
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
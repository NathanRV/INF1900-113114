#include "sonar.h"

void Sonar::calculerDistance(uint8_t sonarPort)
{
    float count = 0;
    char sonarOutput[10];

    PORTB |= 0x01; //Activater Trigger (PINB0)
    attendre_ms(10);
    PORTB &= ~(1 << PORTB0);

    TCNT1 = 0;

    while (!(PINA & (1 << sonarPort)) && TCNT1 < 58800)
        ;

    TCNT1 = 0;

    while ((PINA & (1 << sonarPort)) && TCNT1 < 58800)
        ;

    count = TCNT1;
    distanceSonar1 = (count / 5800);
    dtostrf(distanceSonar1, 3, 2, sonarOutput);
    disp << sonarOutput;
    attendre_ms(2000);
    disp.clear();
}
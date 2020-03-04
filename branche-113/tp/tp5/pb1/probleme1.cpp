#define F_CPU 8000000 

#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"

int main() {
    DDRB = 0xff;
    uint8_t poly[46] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    uint8_t chaineLue[46];
    uint8_t lmao[6] = "LMFAO";
    Memoire24CXXX memoireRobot;
    uint8_t adresse = 0x00;
    memoireRobot.ecriture(adresse, poly, sizeof(poly));
    // for(int i = 0; i < 45; i++) {
    //     memoireRobot.ecriture(adresse, poly[i]);
    //     adresse += 0x01;
    //     _delay_ms(5);
    // }
    _delay_ms(5);
    memoireRobot.lecture(adresse, chaineLue, sizeof(poly));
    // for(int i = 0; i < 45; ++i) {
    //     memoireRobot.lecture(adresse, (uint8_t *)chaineLue);
    //     if(chaineLue[i] != poly[i]) {
    //         isSame = false;
    //         break;
    //     }
    //     adresse += 0x01;
    //     _delay_ms(5);
    // }
    for(int i = 0; i < 45; ++i) {
        if(chaineLue[i] != lmao[i]) {
            PORTB = 0x02;
        } else {
            PORTB = 0x01;
        }
    }
    for(;;) {}
    return 0;
}
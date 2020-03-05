#include "interactionUART.h"

void transmissionUART(uint8_t donnee) {
        /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0))) {};
    /* Copy 9th bit to TXB8 */
    UCSR0B &= ~(1 << TXB80);

    if (donnee & 0x0100){
        UCSR0B |= (1 << TXB80);
    }
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

void ecrireMessageMemoire(Memoire24CXXX* memoire, uint8_t* chaine) {
    memoire->ecriture(0x00, chaine, sizeof(chaine));
    _delay_ms(5);
}
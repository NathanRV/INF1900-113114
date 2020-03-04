#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <memoire_24.h>

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications

    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A =0;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); 
    //modifie  receive,transfer enabled

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C |= (1 << UCSZ11) | (1 << UCSZ10); //char size
}

// De l'USART vers le PC

void transmissionUART(uint8_t donnee)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0))){};
    /* Copy 9th bit to TXB8 */
    UCSR0B &= ~(1 << TXB80);

    if (donnee & 0x0100){
        UCSR0B |= (1 << TXB80);
    }
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main()
{
    DDRD = OUTPUT_PORT;

    initialisationUART();

    char mots[21] = "Le robot en INF1900\n";
    uint8_t i, j;
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 20; j++)
        {
            transmissionUART(mots[j]);
        }
    }


    return 0;
}
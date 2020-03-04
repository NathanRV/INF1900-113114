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

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //modifie  receive,transfer enabled

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


void ecrireMessageMemoire(Memoire24CXXX* memoire,uint8_t* chain) {  
    memoire->ecriture(0x00,chain, sizeof(chain));
    _delay_ms(5);
}

int main()
{
    //Initialisation
    DDRD = OUTPUT_PORT;
    initialisationUART();
    Memoire24CXXX memoire = Memoire24CXXX();
    
    //message
    char chain[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";  


    //Écriture message en memoire
    ecrireMessageMemoire(&memoire,(uint8_t*) &chain);

    char readChain[0xff]; //initialize empty char table
    memoire.lecture(0x00, (uint8_t *)&readChain, sizeof(chain)); //read value

    //transmission UART
    for(uint8_t j=0;j<sizeof(readChain)-1;j++){
        transmissionUART(readChain[j]);
    }

    return 0;
}


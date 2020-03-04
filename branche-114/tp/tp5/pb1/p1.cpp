#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <memoire_24.h>

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;
const uint8_t RED = 0b10;
const uint8_t GREEN = 0b01;

int main()
{
    DDRD = OUTPUT_PORT;
    const uint8_t longueur = 45;
    char chain[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";

    Memoire24CXXX memoire; //call default constructor
    memoire.ecriture(0x00, (uint8_t *)&chain, longueur); //write to mem

    //delay 5 ms to give time to write memory
    _delay_ms(5);

    char readChain[45]; //initialize empty char table
    memoire.lecture(0x00, (uint8_t *)&readChain, longueur); //read value


    bool identic = true;
    for (int i = 0; i < longueur; i++)
    {
        if (chain[i] != readChain[i])
        {
            identic = false;
        }
    }

    if (identic == true)
    {
        PORTD = GREEN;
    }
    else
    {
        PORTD = RED;
    }
    return 0;
}
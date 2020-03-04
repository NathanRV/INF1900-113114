#define F_CPU 8000000


#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;

void ajustementPWM (uint8_t pourcentage) {

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = pourcentage; 
    //Output compare Register 1A correspond à D6 (OC1A)
    
    OCR1B = pourcentage;
    //Output compare Register 1B correspond à D5 (OC1B)
    
    // division d'horloge par 8 - implique une frequence de PWM fixe

    //Voir p.123 & section 16.10.4
    TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1); //Table 16-4.
    //  COM1A1&COM1B1:Clear OCnA/OCnB on Compare Match when up-counting. 
    //  Set OCnA/OCnB on Compare Match when downcounting.
    //  WGM10:PWM, phase correct, 8-bit
    TCCR1B |= (1 << CS11); //prescaler 8

    TCCR1C = 0; 
}

int main(){
    TCNT1 = 0; //intialise counter at 0
    DDRD = OUTPUT_PORT;
    ajustementPWM(255); //100%
    _delay_ms(2000);
    ajustementPWM(191); //75%
    _delay_ms(2000);
    ajustementPWM(127); //50%
    _delay_ms(2000);
    ajustementPWM(64); //25%
    _delay_ms(2000);
    ajustementPWM(0); //0%

    return 0;
}

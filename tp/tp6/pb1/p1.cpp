#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;
const uint8_t RED = 0b10;
const uint8_t GREEN = 0b01;
const uint8_t NO_COLOR = 0b00;

//À REVOIR
enum State
{
    INIT = 0,
    GREEN_R,
    RED,
    OFF,
    GREEN_H,
    NB_STATES
};

void initialisation(void)
{
    /*cli est une routine qui bloque toutes les interruptions.
    Il serait bien mauvais d'être interrompu alors que
    le microcontroleur n'est pas prêt...*/
    cli();

    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = OUTPUT_PORT;
    DDRB = OUTPUT_PORT;
    DDRC = OUTPUT_PORT;
    DDRD = INPUT_PORT;

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= 0b01;

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR(INT0_vect)
{
    /*  laisser un delai avant de confirmer la réponse du
    bouton-poussoir: environ 30 ms (anti-rebond)        */
    _delay_ms(30);

    if (CHANGED_BUTTON_PRESSED_STATE)
    {
        // se souvenir ici si le bouton est pressé ou relâché
        pastPressedState = !pastPressedState;
        
        /*  changements d'états tels que ceux de la
        semaine précédente                          */
        increaseState(currentState);
    }

    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0);
}

void increaseState(volatile State &currentState)
{
    int counter = int{currentState};
    counter = (counter + 1) % NB_STATES; //recommence a INIT si on atteint la fin des states
    currentState = static_cast<State>(counter);
}

int main()
{
	initialisation();
    for (;;)
    {
     switch (currentState) //switches according to state
        {
        case State::NB_STATES://handles the error

        case State::INIT:
            PORTC=RED;

        case State::GREEN_R:
        	PORTC=GREEN;

        case State::RED:
        	PORTC=RED;

        case State::OFF:
        	PORTC=NO_COLOR;

        case State::GREEN_H:
        	PORTC=GREEN;
        }
    }

    return 0;
}
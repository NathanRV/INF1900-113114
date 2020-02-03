/*
    Date:       20-01-2020
    Authors:    David Saikali, 2015144
                Nathan Ramsay-Vejlens 1989944
    File name:  p2.cpp
*/

/*
    IO description: 
    The output LED is connected to PORTC, specifically C1 and C2, using a wire we prepared.
    The input is the interrupt button found on the motherboard. It is connected to PORTD through the motherboard itself.

    General description:
    The LED follows a series of predefined light colors depending on the pressing and releasing of the input button.
*/

/*      The following table shows the possible states and state relations 
+--------------+--------+--------------+--------+
| Current State| Button | Next State   | Output |
+--------------+--------+--------------+--------+
| INIT         |      0 | INIT         | Red    |
| INIT         |      1 | AMBER        | Red    |
| AMBER        |      0 | GREEN_RELEASE| Amber  |
| AMBER        |      1 | AMBER        | Amber  |
| GREEN_RELEASE|      0 | GREEN_RELEASE| Green  |
| GREEN_RELEASE|      1 | RED          | Green  |
| RED          |      0 | OFF          | Red    |
| RED          |      1 | RED          | Red    |
| OFF          |      0 | OFF          | Off    |
| OFF          |      1 | GREEN_HELD   | Off    |
| GREEN_HELD   |      0 | INIT         | Red    |
| GREEN_HELD   |      1 | GREEN_HELD   | Green  |
+--------------+--------+--------------+--------+
*/

/*  
    The following states were abbreviated to make it easier on the programming team : INIT, AMBER, GREEN_R, RED, OFF, GREEN_H.
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define IS_PRESSED (PIND & 0x04)
#define CHANGED_BUTTON_PRESSED_STATE ((!pastPressedState && IS_PRESSED) || (pastPressedState && !IS_PRESSED))

const int DELAY_TIME = 5;       //in ms

const int COLOR_RED = 0b01;
const int COLOR_GREEN = 0b10;
const int COLOR_NONE = 0b00;

const int OUTPUT_PORT = 0xff;
const int INPUT_PORT = 0x00;

enum State
{
    INIT = 0,
    AMBER,
    GREEN_R,
    RED,
    OFF,
    GREEN_H,
    NB_STATES
};

volatile bool pastPressedState = false;
volatile State currentState = State(INIT);

void printRedLight()
{
    PORTC = COLOR_RED;
    _delay_ms(DELAY_TIME);
}

void printGreenLight()
{
    PORTC = COLOR_GREEN;
    _delay_ms(DELAY_TIME);
}

void printNoLight()
{
    PORTC = COLOR_NONE;
    _delay_ms(DELAY_TIME);
}

void printAmberLight()
{
    printRedLight();
    printGreenLight();
}

void increaseState(volatile State &currentState)
{
    int counter = int{currentState};
    counter = (counter + 1) % NB_STATES; //recommence a INIT si on atteint la fin des states
    currentState = static_cast<State>(counter);
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

int main()
{

    initialisation();
    for (;;)
    {
     switch (currentState) //switches according to state
        {
        case State::NB_STATES://handles the error
            break;
        case State::INIT:
            printRedLight();
            break;

        case State::AMBER:
            printAmberLight();
            break;

        case State::GREEN_R:
            printGreenLight();
            break;

        case State::RED:
            printRedLight();
            break;

        case State::OFF:
            printNoLight();
            break;

        case State::GREEN_H:
            printGreenLight();
        }
    }

    return 0;
}
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

#include <avr/io.h>

#define F_CPU 8000000UL
#define IS_PRESSED (PIND & 0x04)

#include <util/delay.h>

const int DELAY_TIME = 5;       //in ms
const int LIGHT_UP_TIME = 1000; //in ms

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
    GREEN_H
};

bool isButtonPressed()
{
    if (IS_PRESSED)
    {
        _delay_ms(DELAY_TIME);
        if (IS_PRESSED)
        {
            return true;
        }
    }
    return false;
}

void printRedLight()
{
    PORTC = COLOR_RED;
    _delay_ms(DELAY_TIME);
}

void printAmberLight()
{
    PORTC = COLOR_RED;
    _delay_ms(DELAY_TIME);
    PORTC = COLOR_GREEN;
    _delay_ms(DELAY_TIME);
}

void printGreenLight()
{
    PORTC = COLOR_GREEN;
    _delay_ms(DELAY_TIME);
}

void increaseState(State &currentState)
{
    int counter = int{currentState};
    counter++;
    currentState = static_cast<State>(counter);
}

int main()
{
    DDRA = OUTPUT_PORT;
    DDRB = OUTPUT_PORT;
    DDRC = OUTPUT_PORT;
    DDRD = INPUT_PORT;

    State currentState = State(INIT);

    for (;;)
    {
        switch (currentState) //switches according to state
        {
        case State::INIT:
            printRedLight();
            if (isButtonPressed())
            {
                increaseState(currentState);
            }
            break;
        case State::AMBER:
            printAmberLight();
            if (!isButtonPressed())
            {
                increaseState(currentState);
            }
            break;
        case State::GREEN_R:
            printGreenLight();
            if (isButtonPressed())
            {
                increaseState(currentState);
            }
            break;
        case State::RED:
            printRedLight();
            if (!isButtonPressed())
            {
                increaseState(currentState);
            }
            break;
        case State::OFF:
            PORTC = 0b00;
            if (isButtonPressed())
            {
                increaseState(currentState);
            }
            break;
        case State::GREEN_H:
            printGreenLight();
            if (!isButtonPressed())
            {
                currentState = State::INIT;
            }
        }
    }

    return 0;
}

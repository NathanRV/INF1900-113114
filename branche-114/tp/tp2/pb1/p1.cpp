/*
    Date:       20-01-2020
    Authors:    David Saikali, 2015144
                Nathan Ramsay-Vejlens 1989944
    File name:  p1.cpp
*/

/*
    IO description: 
    The output LED is connected to PORTC, specifically C1 and C2, using a wire we prepared.
    The input is the interrupt button found on the motherboard. It is connected to PORTD through the motherboard itself.

    General description:
    The LED lights up in red after having pressed and released the button 5 times, at which point it resets to its initial state.
*/

/*      The following table shows the possible states and state relations 
+--------------+--------+--------------+--------+
| Current State| Button | Next State   | Output |
+--------------+--------+--------------+--------+
| INIT         | 0      | INIT         | Off    |
| INIT         | 1      | PRESS1       | Off    |
| PRESS1       | 0      | PRESS1       | Off    |
| PRESS1       | 1      | PRESS2       | Off    |
| PRESS2       | 0      | PRESS2       | Off    |
| PRESS2       | 1      | PRESS3       | Off    |
| PRESS3       | 0      | PRESS3       | Off    |
| PRESS3       | 1      | PRESS4       | Off    |
| PRESS4       | 0      | PRESS4       | Off    |
| PRESS4       | 1      | PRESS5       | Off    |
| PRESS5       | x      | INIT         | Red    |
+--------------+--------+--------------+--------+
*/

#include <avr/io.h>

#define F_CPU 8000000UL
#define IS_PRESSED (PIND & 0x04)

#include <util/delay.h>

const int DELAY_TIME = 5;       //in ms
const int LIGHT_UP_TIME = 1000; //in ms

const int COLOR_RED = 0b01;
const int COLOR_NONE = 0b00;

const int OUTPUT_PORT = 0xff;
const int INPUT_PORT = 0x00;

enum State //all possible states
{
    INIT = 0,
    PRESS1,
    PRESS2,
    PRESS3,
    PRESS4,
    PRESS5
};

bool isPressedButtonReleased() //returns true once the pressed button is released. Includes a rebound filter.
{
    if (IS_PRESSED)
    {
        _delay_ms(DELAY_TIME);
        if (IS_PRESSED)
        {
            while (IS_PRESSED)
            {
            }
            return true;
        }
    }
    return false;
}

void printRedLight(int lightUpTime)
{
    int counter = lightUpTime / DELAY_TIME;
    for (int i = 0; i < counter; i++)
    {
        PORTC = COLOR_RED;
        _delay_ms(DELAY_TIME);
    }
    PORTC = COLOR_NONE;
}

void increaseState(State &currentState) //increases the state to the next one in the enum
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

    State currentState = State::INIT;

    for (;;)
    {
        switch (currentState)
        {
        case State::INIT:
            if (isPressedButtonReleased())
            {
                increaseState(currentState);
            }
            break;
        case State::PRESS1:
            if (isPressedButtonReleased())
            {
                increaseState(currentState);
            }
            break;
        case State::PRESS2:
            if (isPressedButtonReleased())
            {
                increaseState(currentState);
            }
            break;
        case State::PRESS3:
            if (isPressedButtonReleased())
            {
                increaseState(currentState);
            }
            break;
        case State::PRESS4:
            if (isPressedButtonReleased())
            {
                increaseState(currentState);
            }
            break;
        case State::PRESS5:
            printRedLight(LIGHT_UP_TIME);
            currentState = State(INIT);
        }
    }

    return 0;
}

/*
    Date:       27-01-2020
    Authors:    David Saikali, 2015144
                Nathan Ramsay-Vejlens 1989944
    File name:  p1.cpp
*/

/*
    IO description: 
    The output LED is connected to PORTC, specifically C1 and C2, using a wire we prepared.
    The input is the interrupt button found on the motherboard. It is connected to PORTD through the motherboard itself.

    General description:
    The LED lights up in red and slowly decreases until off in 3 seconds. Same for green color.
*/

#define F_CPU 8000000UL
#define IS_PRESSED (PIND & 0x04)

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>

const int FORWARDS = 0b10;
const int BACKWARDS = 0b11;
const int STILL = 0b00;

const int OUTPUT_PORT = 0xff;
const int INPUT_PORT = 0x00;

const int RUN_TIME = 2000; //in ms (miliseconds)

const long SECONDS_TO_MICRO = 1000000;
const int SECONDS_TO_MILI = 1000;
const int CPU_CYCLES_PER_DELAY_ITERATION = 4;

void delayMS(int ms)
{
    _delay_loop_2(F_CPU / (1000 * 4) * ms);
}

void delayUS(int us)
{
    _delay_loop_2(floor(F_CPU / (SECONDS_TO_MICRO * CPU_CYCLES_PER_DELAY_ITERATION) * us));
}

enum State
{
    ZERO = 0,
    QUARTER,
    HALF,
    THREE_QUARTER,
    FULL,
    NB_STATES
};

void increaseState(State &currentState) //increases the state to the next one in the enum
{
    int counter = int{currentState};
    counter++;
    currentState = static_cast<State>(counter);
};

void spinWheelVaryingIntensity(int intensity, int period, bool isGoingForward)
{
    int loopIterations = round(RUN_TIME / period * SECONDS_TO_MILI);
    int ratioPercentage = intensity * 100 / 4;
    int upTime = period * ratioPercentage / 100;

    if (isGoingForward)
    {
        for (int i = 0; i < loopIterations; i++)
        {
            PORTB = FORWARDS;
            delayUS(upTime);

            PORTB = STILL;
            delayUS(period - upTime);
        }
    }
    else
    {
        for (int i = 0; i < loopIterations; i++)
        {
            PORTB = BACKWARDS;
            delayUS(upTime);

            PORTB = STILL;
            delayUS(period - upTime);
        }
    }
};

void runVaryingFrequency(int frequency)
{
    int period = round(1000000.0 / frequency); //in us (microseconds)
                                               //State currentState = State::ZERO;

    //for (int i = 0; i < NB_STATES; i++)
    //{
    spinWheelVaryingIntensity(/*int{currentState}*/ 1, period, true);
    //increaseState(currentState);
    //}
};

int main()
{
    DDRA = OUTPUT_PORT;
    DDRB = OUTPUT_PORT;
    DDRC = OUTPUT_PORT;
    DDRD = INPUT_PORT;

    //spinWheelVaryingIntensity(1, 16667, true);
    for (;;)
    {
        PORTB = FORWARDS;
        delayMS(4000);
        PORTB = STILL;
        delayMS(4000);
    }

    /*    for (int i = 0;;)
    {
        PORTB = FORWARDS;
        delayUS(4000);
    }*/

    runVaryingFrequency(60);
    //runVaryingFrequency(400);

    return 0;
}

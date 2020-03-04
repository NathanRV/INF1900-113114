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

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>

#define F_CPU 8000000UL

const int COLOR_GREEN = 0b01;
const int COLOR_RED = 0b10;
const int COLOR_NONE = 0b00;

const int OUTPUT_PORT = 0xff;
const int INPUT_PORT = 0x00;

const int PERIOD = 1000;   //in us (microseconds)
const int RUN_TIME = 3000; //in ms (miliseconds)

void delay(int us)
{
    _delay_loop_2(F_CPU / (4000000) * us);
}

int main()
{
    DDRA = OUTPUT_PORT;
    DDRB = OUTPUT_PORT;
    DDRC = OUTPUT_PORT;
    DDRD = INPUT_PORT;

    for (;;)
    {

        for (int i = 0; i < RUN_TIME; i++)
        {
            int decrementIntensity = floor(i * PERIOD / RUN_TIME);

            PORTC = COLOR_RED;
            delay(PERIOD - decrementIntensity);

            PORTC = COLOR_NONE;
            delay(decrementIntensity);
        }

        for (int i = 0; i < RUN_TIME; i++)
        {
            int decrementIntensity = floor(i * PERIOD / RUN_TIME);

            PORTC = COLOR_GREEN;
            delay(PERIOD - decrementIntensity);

            PORTC = COLOR_NONE;
            delay(decrementIntensity);
        }
    }

    return 0;
}

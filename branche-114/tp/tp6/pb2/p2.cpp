/*
    Date:       27-02-2020
    Authors:    David Saikali, 2015144
                Nathan Ramsay-Vejlens 1989944
    File name:  p2.cpp
*/

/*
    IO description: 
    The output LED is connected to PORTB, specifically B1 and B2, 
    using a wire we prepared.
    The input is the light perceived by the photoresistor placed on the breadboard.
    It is connected to PORTA (P1 and P2) through a wire. 
    PORTA gives the power to the breadboard.
    The breadboard follows the setup given on the website.

    General description:
    The LED lights green in absence of light, amber when there is a medium level of light
    and red when there is a strong light (a cellphone camera's light is an example).
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;
const uint8_t RED = 0b10;
const uint8_t GREEN = 0b01;

/*
    The values were found experimentally and may vary from one environment to the next. 
    There is a way to set these values dynamically but it leaves too much room for error and the constants would depend on the initial light level of the room you were in. 
    Therefore we decided against doing so and decided to instead implement this comment to explain our thought processs
*/
const uint8_t LOW_LIGHT_LEVEL = 150;
const uint8_t MED_LIGHT_LEVEL = 220;

int main()
{
    DDRA = INPUT_PORT;
    DDRB = OUTPUT_PORT;

    can reader;
    uint16_t tmp;
    uint8_t lightLevel;

    for (;;)
    {
        tmp = reader.lecture(PINA);
        lightLevel = tmp >> 2;

        if (lightLevel < LOW_LIGHT_LEVEL)
        {
            PORTB = GREEN;
        }
        else if (lightLevel < MED_LIGHT_LEVEL)
        {
            PORTB = GREEN;
            _delay_ms(5);
            PORTB = RED;
            _delay_ms(5);
        }
        else
        {
            PORTB = RED;
        }
    }

    return 0;
}
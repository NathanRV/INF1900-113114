/*
    Authors:    Nathan Ramsay-Vejlens
                David Saikali
    Date:       24-02-2020
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
const uint8_t LOW_LIGHT_LEVEL = 170;
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
            _delay_ms(5);
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
            _delay_ms(5);
        }
    }

    return 0;
}
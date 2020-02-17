/*
 * Nom fichier:p2.cpp
 * Auteurs: 
 *
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;
const uint8_t RED = 0b10;
const uint8_t GREEN = 0b01;

int main()
{
    DDRD = OUTPUT_PORT;



    return 0;
}
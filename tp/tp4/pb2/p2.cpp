#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define IS_PRESSED (PIND & 0x04)

const int DELAY_TIME = 5; //in ms

const int COLOR_RED = 0b01;
const int COLOR_GREEN = 0b10;
const int COLOR_NONE = 0b00;

const int OUTPUT_PORT = 0xff;
const int INPUT_PORT = 0x00;

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

volatile bool timeExpired = false;
volatile bool buttonPressed = false;

ISR(TIMER1_COMPA_vect)
{
    timeExpired = true;
}

ISR(INT0_vect)
{
    _delay_ms(30);

    if (IS_PRESSED)
    {
        buttonPressed = true;
    }

    EIFR |= (1 << INTF0);
}

void startTimer(uint16_t duration)
{
    //CTC mode of the timer 1 with the clock divided by 1024 (2^10)

    TCNT1 = 0;

    // interruption after the required duration
    OCR1A = duration;

    TCCR1A = 0b01010000;
    /*
        7-6:Compare output mode channel A
        5-4:Compare output mode channel B
        3-2:Reserved
        1-0:
    */

    TCCR1B = 0b11000000;
    /*  Bit order and signification
        7:Filter to have 4 CPU actions per clock cycle (1 = on)
        6:Rising (1) or falling (0) edge
        5:Reserved
        4-3:PTCCRnA thing
        2-0:Clock Select
    */

    TCCR1C = 0;

    TIMSK1 = 0; //masque
}

int main()
{
    startTimer();
    return 0;
}

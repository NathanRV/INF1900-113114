#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

const int COLOR_GREEN = 0b01;
const int COLOR_RED = 0b10;
const int COLOR_NONE = 0b00;

const int PERIOD = 1000;   //in microseconds (us)
const int RUN_TIME = 3000; //in miliseconds (s)

void delay(int nombre)
{
    for (int i = 0; i < nombre; i++)
    {
        _delay_us(1);
    }
}

void trial_1()
{

    DDRC = 0xff;                                          // PORT D is in output mode
    int loopIterations = RUN_TIME / PERIOD * 1000;        //3000
    int ratioIterationToPeriod = loopIterations / PERIOD; //3
    int delayTime;
    int a = loopIterations;
    for (;;)
    {
        for (int i = 3000; i > 0; i--)
        {
            delayTime = a / ratioIterationToPeriod;
            PORTC = COLOR_GREEN;
            delay(delayTime);

            PORTC = COLOR_NONE;
            delay(PERIOD - delayTime);
            a--;
        }
    }
}

void trial_2()
{
    for (;;)
    {
        DDRC = 0xff;                                          // PORT D is in output mode
        int loopIterations = RUN_TIME / PERIOD * 1000;        //3000
        int ratioIterationToPeriod = loopIterations / PERIOD; //3

        int delayTime = PERIOD;
        DDRC = 0xff; // PORT D is in output mode
        for (int i = 0; i < loopIterations; i++)
        {
            for (int j = 0; j < delayTime; j++)
            {
                PORTC = COLOR_GREEN;
                delay(delayTime);
            }

            for (int k = 0; k < PERIOD - delayTime; k++)
            {
                PORTC = COLOR_NONE;
                delay(PERIOD - delayTime);
            }
            delayTime = (delayTime - 1) / ratioIterationToPeriod;
        }
    }
}

int main()
{
}

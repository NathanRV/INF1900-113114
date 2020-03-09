/*
    Date:       27-02-2020
    Authors:    David Saikali, 2015144
                Nathan Ramsay-Vejlens 1989944
    File name:  p1.cpp
*/

/*
    IO description: 
    The output LED is connected to PORTC, specifically C1 and C2, 
    using a wire we prepared.
    The input is the interrupt button found on the breadboard as well as 
    the timer register inside the motherboard. 
    It is connected to PORTD through a wire. PORTA gives the power to the breadboard.
    The breadboard follows the setup given on the website.

    General description:
    The LED follows a series of predefined light colors starting after the interruptions.
*/

/*      The following table shows the possible states and state relations 
+---------------+----------------------------------------+------------+----------+
| Current State | Input                                  | Next State | Output   |
+---------------+----------------------------------------+------------+----------+
| INIT          | None                                   | INIT       | None     |
+---------------+----------------------------------------+------------+----------+
| INIT          | INT0 followed by INT0 or TIMER1_COMPA  | CONDITION  | None     |
+---------------+----------------------------------------+------------+----------+
| CONDITION     | None                                   | INIT       | Multiple |
+---------------+----------------------------------------+------------+----------+
| NB_STATES     | None                                   | INIT       | None     |
+---------------+----------------------------------------+------------+----------+
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;
const uint8_t COLOR_RED = 0b10;
const uint8_t COLOR_GREEN = 0b01;
const uint8_t NO_COLOR = 0b00;

//Variable 
volatile bool isButtonHeld = true;
volatile bool conditionFulfilled = false;
volatile uint8_t counterRunTimes;

//Delay miliseconds function 
void delayMs(uint16_t ms){
    for(uint16_t i=0;i<ms;i++){ //delay x ms
        _delay_loop_2(2000); //4 CPU cycles * 2 000=8 000
        //8 000*1000Ms=8 000 000 instructions = 1sec
    }

}

//States
enum State
{
    INIT = 0,//Timer starts
    CONDITION, //light routine launched
    NB_STATES
};

volatile State currentState = State::INIT;

/*
    8 000 000 instruc/s
    prescaler of 64
    125 000 instruc/s
    10 increment/s so 12 500 duration to have 1 increment per 0,1s
*/
void startTimer(){
    //CTC mode of the timer 1 with the clock divided by 1024 (2^10)
    TCNT1 = 0;

    // interruption after the required duration
    OCR1A = 12500;

    TCCR1B |= (1<<CS11) | (1<<CS10) | (1<<WGM12) ;
    //prescaler of 64 and CTC mode

    TIMSK1 |= (1 << OCIE1A);
    //compare output A mode enabled

    //Overflow initialize
    counterRunTimes= 0;
}

void increaseState(volatile State &currentState)
{
    int stateNum = int{currentState};
    stateNum = (stateNum+ 1) % NB_STATES; //reset to INIT if reached end
    currentState = static_cast<State>(stateNum);
}

void initialisation(void)
{
    // cli blocks interruptions
    cli();

    // Port directions
    DDRA = OUTPUT_PORT;
    DDRB = OUTPUT_PORT;
    DDRC = OUTPUT_PORT;
    DDRD = INPUT_PORT;

    // Allows interruption of INT0
    EIMSK |= (1 << INT0);

    // Any edge of INT0 generates an interrupt request
    EICRA |= (1<<ISC00); 

    // sei deblocks interruptions
    sei();
}


// Timer interrupt function
ISR(TIMER1_COMPA_vect){
    if(!(PIND & 0x04) && !conditionFulfilled && counterRunTimes==120){
        conditionFulfilled = true;
        increaseState(currentState);
    }
    counterRunTimes++;
}


// Button interrupt function
ISR(INT0_vect)
{
    // debounce       
    _delay_ms(30);
    if (!(PIND & 0x04))
    {
        //start timer
        startTimer();
    }
    else if(!conditionFulfilled){
        conditionFulfilled=true;
        increaseState(currentState);
    }
    // Clear flag to permit new interrupts of INT0
    EIFR |= (1 << INTF0);
}


//Routine
//Green blinking 0,5 seconds, no color for 2 sec
//Red blinks 2 times/second for counter/2 times
//Green for 1 second
//return to init state
void routine(){
    for(uint8_t i=0;i<5;i++){ //5*0,1s=0,5s
        PORTC=COLOR_GREEN;
        delayMs(uint16_t(50)); //delay 50 ms=0,05s
        PORTC=NO_COLOR;
        delayMs(uint16_t(50)); //delay 50 ms=0,05s
    }
    
    PORTC=NO_COLOR;
    delayMs(uint16_t(2000)); //delay 2 s
       

    uint8_t currentCounter;
    currentCounter=counterRunTimes;

    for(uint8_t i =0;i<currentCounter; i++){
        PORTC=COLOR_RED;
        delayMs(uint16_t(100)); //delay 100 ms=0,1s
        PORTC=NO_COLOR;
        delayMs(uint16_t(400)); //delay 400 ms=0,4s
    }


    PORTC=COLOR_GREEN;
    delayMs(uint16_t(1000)); //delay 1000 ms=1s
    currentState=State::INIT;//return to init state
    conditionFulfilled=false; //reset condition bool
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

            case State::INIT:  //Timer starts when button pressed
                PORTC=NO_COLOR;
                break;

            case State::CONDITION: //Green 0,5 seconds, wait 2 sec ...                
                routine();
                break;
                
        }
    }
    
    return 0;
}

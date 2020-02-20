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

//Delay miliseconds function (NOT WORKING RIGHT BECAUSE CONVERSION UINT8_T INT)
void delayMs(uint8_t Ms){
    if(Ms<0){
        Ms=-Ms;
    }
    uint8_t ms=Ms;
    for(uint8_t i=0;i<ms;i++){ //delay 1 s
        _delay_loop_2(2000); //4 CPU cycles * 2 000=8 000
        //8 000*Ms=8 000 000 instructions = 1sec
    }

}

//États
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
void partirMinuterie(){
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
    stateNum = (stateNum+ 1) % NB_STATES; //recommence a INIT si on atteint la fin des states
    currentState = static_cast<State>(stateNum);
}

void initialisation(void)
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
     //le microcontroleur n'est pas prêt...
    cli();

    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = OUTPUT_PORT;
    DDRB = OUTPUT_PORT;
    DDRC = OUTPUT_PORT;
    DDRD = INPUT_PORT;

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1<<ISC00); 

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}


//Interruption du timer
ISR(TIMER1_COMPA_vect){
    if(!(PIND & 0x04) && !conditionFulfilled && counterRunTimes==120){
        conditionFulfilled = true;
        increaseState(currentState);
    }
    counterRunTimes++;
}


// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR(INT0_vect)
{
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)        
    _delay_ms(30);
    if (!(PIND & 0x04))
    {
        //partir minuterie
        partirMinuterie();
    }
    else if(!conditionFulfilled){
        conditionFulfilled=true;
        increaseState(currentState);
    }
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0);
}


//Routine
//Green 0,5 seconds, no color for 2 sec
//Red blinks 2 times/second for counter/2 times
//Green for 1 second
//return to init state
void routine(){
    PORTC=COLOR_GREEN;
    for(uint8_t i=0;i<50;i++){ //delay 0,5 s
        _delay_loop_2(20000); //4 CPU cycles * 20 000=80 000
        //80 000*50=4 000 000 instructions = 0,5sec
    }
    PORTC=NO_COLOR;
    for(uint8_t i=0;i<200;i++){ //delay 2 s
        _delay_loop_2(20000); //4 CPU cycles * 20 000=80 000
        //80 000*200=16 000 000 instructions = 2sec
    }

    uint8_t currentCounter;
    currentCounter=counterRunTimes;

    for(uint8_t i =0;i<currentCounter; i++){
        PORTC=COLOR_RED;
        _delay_loop_2(20000); //0,1 sec
        PORTC=NO_COLOR;
        for(uint8_t i=0;i<50;i++){ //delay 0,5 s
            _delay_loop_2(20000); //4 CPU cycles * 20 000=80 000
            //80 000*50=4 000 000 instructions = 0,5sec
        }
    }


    PORTC=COLOR_GREEN;
    for(uint8_t i=0;i<100;i++){ //delay 1 s
        _delay_loop_2(20000); //4 CPU cycles * 20 000=80 000
        //80 000*100=8 000 000 instructions = 1sec
    }
    currentState=State::INIT;//return init state
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

            case State::CONDITION: //Green 0,5 seconds, wait 2 sec                
                routine();
                break;
                
        }
    }
    
    return 0;
}

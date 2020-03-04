#define F_CPU 8000000UL
#define IS_PRESSED (PIND & 0x04)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


const long SECONDS_TO_MICRO = 1000000;
const int SECONDS_TO_MILI = 1000;
const int CPU_CYCLES_PER_DELAY_ITERATION = 4;

const int DELAY_TIME = 10; //in s

const int COLOR_RED = 0b01;
const int COLOR_GREEN = 0b10;
const int COLOR_NONE = 0b00;

const int OUTPUT_PORT = 0xff;
const int INPUT_PORT = 0x00;

volatile bool timeExpired = false;
volatile bool buttonPressed = false;
volatile uint8_t tot_overflow;

void delayMS(int ms)
{
    _delay_loop_2(F_CPU / (SECONDS_TO_MILI * CPU_CYCLES_PER_DELAY_ITERATION) * ms);
}

void delayUS(int us)
{
    _delay_loop_2(floor(F_CPU / (SECONDS_TO_MICRO * CPU_CYCLES_PER_DELAY_ITERATION) * us));
}

void printRedLight()
{
    PORTC = COLOR_RED;
}

void printGreenLight()
{
    PORTC = COLOR_GREEN;
}

void printNoLight()
{
    PORTC = COLOR_NONE;
}

void initialisation(void)
{

    /*cli est une routine qui bloque toutes les interruptions.
    Il serait bien mauvais d'être interrompu alors que
    le microcontroleur n'est pas prêt...*/
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
    EICRA |= 0b01;

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

void startTimer(uint16_t duration)
{
    //CTC mode of the timer 1 with the clock divided by 1024 (2^10)
    TCNT1 = 0;

    // interruption after the required duration
    OCR1A = duration;

    TCCR1B = 0b00000010; //
    // last three digits are prescaler (prescaler of 8=010)

    TIMSK1 |= (1 << TOIE1);//= 0b00000100;
    //Overflow Interrupt enabled //masque

    //Overflow initialize
    tot_overflow = 0;
}


/*
    65535/8 000 000=8,192ms = max delay
    upon using prescaler of 8 timer frequency = 1000Khz
    65535/1 000 000=0,065535s
    10s /0,065535 s=152,59 
    should overflow 153 times
    1s/0,065535s=15,25
    should overflow 15
*/
ISR(TIMER1_OVF_vect)
{
    tot_overflow++;
    if(tot_overflow< 15 && timeExpired && buttonPressed){
        printGreenLight();
    }
    else if(tot_overflow> 15 && timeExpired && !buttonPressed){
        printRedLight();
    }
    if (tot_overflow> 153 && !timeExpired)
    {
        printRedLight();
        delayMS(100);
        printNoLight();
        tot_overflow = 0;
        timeExpired=true;
    }
}

ISR(INT0_vect)
{
    _delay_ms(30); //rebound filter

    if (IS_PRESSED && timeExpired && !buttonPressed)
    {
        buttonPressed = true;
    }

    EIFR |= (1 << INTF0);
}


int main()
{
    initialisation();

    startTimer(65535);  //max delay
    while (1)
    {
        //do nothing
        //interrupts handle situations
    }
}

#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t OUTPUT_PORT = 0xff;
const uint8_t INPUT_PORT = 0x00;

/* Function description :
/ Param : percent (0 to 100)
/ Returns : void
/ Creates PWM on PIND
*/
void adjustPWM ( uint8_t percent ) {
	DDRD = OUTPUT_PORT; //set pins to output
    TCNT1 = 0; //intialise counter at 0

	//f=frequency, N=prescaler factor
	//fOCnA=fclk/2N(1+OCRnX)

	//Logical equation to transform percent
	uint8_t maxValueCounter = 0xFFFF; //65 535
	uint8_t maxValuePercent = round(maxValueCounter / 100); //655
	uint8_t value = maxValuePercent * percent;

	//Set compare value
	OCR1A = value ;
	OCR1B = value ;

	//Timer/Counter Control Register 1 A
	TCCR1A |= (1<<COM1A1) |(1<<COM1B1) ; 
	//OC1A OC1B cleared on Compare Match, set at BOTTOM
	//fast PWM

	//Timer/Counter Control Register 1 B
	//Prescaler
	TCCR1B |= (1 << CS11);
	//Divided by 8 (CS11)
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << WGM11);
	//Fast PWM mode (16 bits) where TOP=ICRn
	ICR1 = maxValueCounter;

	TCCR1C = 0;
}

int main(){
    adjustPWM(100); //100%
    _delay_ms(2000);
    adjustPWM(75); //75%
    _delay_ms(2000);
    adjustPWM(50); //50%
    _delay_ms(2000);
    adjustPWM(25); //25%
    _delay_ms(2000);
    adjustPWM(0); //0%

    return 0;
}
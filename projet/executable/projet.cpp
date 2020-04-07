/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  main.cpp
*/

#include "controleDEL.h"
#include "controleMoteur.h"
#include "capteurs.h"
#include "can.h"
#include "initialisation.h"
#include "constantes.h"
#include "delay.h"
#include "interactionUART.h"
#include "antirebond.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
/**
 * 
 *
 *
 *
 */

void static inline w(void)
{
    cp_wait_ms(2000);
}

int main()
{

    initialiserDDRD(SORTIE);
    initialiserDDRB(SORTIE);
    PORTB = 0b01110000;
    // for (;;)
    // {
    //     PORTD = 0b10000001;
    // }

    LCM disp(&DDRB, &PORTB);

    disp.put('b');
    disp << "wooooooow !!";
    w();
}
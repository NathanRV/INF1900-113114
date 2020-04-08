/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  main.cpp
*/
#define F_CPU 8000000

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

void static inline w(void)
{
    cp_wait_ms(2000);
}

/**
 * Manoeuvre 1 (OK - OK - ATTN)
 * Vitesse initiale : (90, 90).
 * La vitesse de la roue gauche descend graduellement jusqu'à 52, à raison de -1 par 100 ms.
 * À (52, 90), on laisse passer 1000 ms.
 * La vitesse de la roue gauche remonte graduellement jusqu'à 90, à raison de +1 par 100 ms.
 * À (90, 90), on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void manoeuvre1(LCM &disp)
{

    disp << "Manoeuvre 1";
    w();

    for(int i = 90 ; i > 51 ; i--){
        ajusterPWM(i, 90);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for(int i = 52 ; i < 91 ; i++){
        ajusterPWM(i, 90);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    disp.clear();
}

/**
 * Manoeuvre 2 (ATTN - OK - OK)
 * Vitesse initiale : (90, 90).
 * La vitesse de la roue droite descend graduellement jusqu'à 52, à raison de -1 par 100 ms.
 * À (90, 52), on laisse passer 1000 ms.
 * La vitesse de la roue droite remonte graduellement jusqu'à 90, à raison de +1 par 100 ms.
 * À (90, 90), on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void manoeuvre2(LCM &disp)
{
    disp << "Manoeuvre 2";
    w();

    for(int i = 90 ; i > 51 ; i--){
        ajusterPWM(90, i);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for(int i = 52 ; i < 91 ; i++){
        ajusterPWM(90, i);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    disp.clear();
}

/**
 * Manoeuvre 3 (OK - DNGR - DNGR)
 * Vitesse initiale : (-50, 50). On laisse passer 1000 ms.
 * On change la vitesse pour (66, 66) et on laisse passer 2000 ms.
 * On change la vitesse pour (50, -50) et on laisse passer 1000 ms.
 * On change la vitesse pour (78, 78) et on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void manoeuvre3(LCM &disp)
{
    disp << "Manoeuvre 3";
    w();
    ajusterPWM(-50, 50);
    attendre_ms(1000);

    ajusterPWM(66, 66);
    attendre_ms(2000);

    ajusterPWM(50, -50);
    attendre_ms(1000);

    ajusterPWM(78, 78);
    attendre_ms(2000);
    disp.clear();
}

/** Manoeuvre 4 (DNGR - DNGR - OK)
 * Vitesse initiale : (50, -50). On laisse passer 1000 ms.
 * On change la vitesse pour (66, 66) et on laisse passer 2000 ms.
 * On change la vitesse pour (-50, 50) et on laisse passer 1000 ms.
 * On change la vitesse pour (78, 78) et on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void manoeuvre4(LCM &disp)
{
    disp << "Manoeuvre 4";
    w();
    ajusterPWM(50, -50);
    attendre_ms(1000);

    ajusterPWM(66, 66);
    attendre_ms(2000);

    ajusterPWM(-50, 50);
    attendre_ms(1000);

    ajusterPWM(78, 78);
    attendre_ms(2000);
    disp.clear();
}

/** Manoeuvre 5 (DNGR - DNGR - DNGR)
 * Vitesse initiale : (50, -50). On laisse passer 2000 ms.
 * On change la vitesse pour (0, 0) et on passe à l'étape suivante.
 * La vitesse monte graduellement de (0, 0) à (63, 63) à raison de +3 par 125 ms.
 * À (63, 63), on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void manoeuvre5(LCM &disp)
{
    disp << "Manoeuvre 5";
    w();
    ajusterPWM(50, -50);
    attendre_ms(2000);

    ajusterPWM(0, 0);

    for (int i = 0; i < 64; i += 3)
    {
        ajusterPWM(i, i);
        attendre_ms(125);
    }

    attendre_ms(1875); //125 ms deja ecoules
    disp.clear();
}

/** Manoeuvre 6 (ATTN - OK - ATTN)
 * Vitesse initiale : (90, 90).
 * La vitesse descend graduellement de (90, 90) à (41, 41) à raison de -7 par 500 ms.
 * À (41, 41), on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void manoeuvre6(LCM &disp)
{
    disp << "Manoeuvre 6";
    w();
    ajusterPWM(90, 90);

    for (int i = 90; i > 40; i -= 7)
    {
        ajusterPWM(i, i);
        attendre_ms(500);
    }

    attendre_ms(1500); //500 ms deja ecoules
    disp.clear();
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
    disp.clear();
    for (;;)
    {
        //Manoeuvre 1
        manoeuvre1(disp);

        //Manoeuvre 2
        manoeuvre2(disp);

        //Manoeuvre 3
        manoeuvre3(disp);

        //Manoeuvre 4
        manoeuvre4(disp);

        //Manoeuvre 5
        manoeuvre5(disp);

        //Manoeuvre 6
        manoeuvre6(disp);
    }

    return 0;
}
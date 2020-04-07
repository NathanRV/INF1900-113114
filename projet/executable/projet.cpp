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


/**
 * 
 *
 *
 *
 */
void manoeuvre1(){
    //Manoeuvre 1 (OK - OK - ATTN)
    ajusterPWM(90,90);
    for(int i = 90 ; i > 51 ; i--){
        ajusterPWM(90, i);
        attendre_ms(100);
    }
    attendre_ms(1000);
    for(int i = 52 ; i < 91 ; i++){
        ajusterPWM(90, i);
        attendre_ms(100);
    }
    attendre_ms(2000);
}

int main()
{
    initialiserDDRD(SORTIE);
    //initialisationInterruption(SORTIE,SORTIE,SORTIE,ENTREE);
    //tournerRoues(true, true, 99,99);
    for(;;){
        /*PORTD = 0b110001;*/
        attendre_ms(100);
        PORTD |= AVANCERDROITE;
        PORTD |= RECULERGAUCHE;
        PORTD |= AVANCERGAUCHE;/*
        attendre_ms(100);
        PORTD |= 0b1;*/
        //manoeuvre1();
    }

}


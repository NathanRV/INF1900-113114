/*
    Date:       11-04-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  projet.cpp
*/
#define F_CPU 8000000

#include <stdio.h>
#include <stdlib.h>
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
#include <avr/io.h>
#include <avr/interrupt.h>
#include "sonar.h"
#include "robot.h"

/**
+---------------+-----------------+------------+----------+
| Current State | Input           | Next State | Output   |
+===============+=================+============+==========+
| DETECTION     | Bouton poussoir | MANOEUVRE  | Multiple |
+---------------+-----------------+------------+----------+
| MANOEUVRE1    | None            | DETECTION  | Multiple |
+---------------+-----------------+------------+----------+
| MANOEUVRE2    | None            | DETECTION  | Multiple |
+---------------+-----------------+------------+----------+
| MANOEUVRE3    | None            | DETECTION  | Multiple |
+---------------+-----------------+------------+----------+
| MANOEUVRE4    | None            | DETECTION  | Multiple |
+---------------+-----------------+------------+----------+
| MANOEUVRE5    | None            | DETECTION  | Multiple |
+---------------+-----------------+------------+----------+
| MANOEUVRE6    | None            | DETECTION  | Multiple |
+---------------+-----------------+------------+----------+
| MANOEUVREX    | None            | DETECTION  | Multiple |
+---------------+-----------------+------------+----------+
 * 
 * 
 */


//Variables Globales
Etats etatPresent = DETECTION;
LCM disp(&DDRB, &PORTB);
Robot robot;
Sonar sonar;

void static inline w(void)
{
    cp_wait_ms(2000);
}

int main()
{
    initialisationBouton();

    for (;;)
    {
        robot.controlerEtat(etatPresent);
    }

    return 0;
}

ISR(TIMER2_COMPB_vect)
{
    uint8_t gauche;
    uint8_t droite;

    if (Robot::getpGauche() < 0)
        gauche = -Robot::getpGauche();
    else
        gauche = Robot::getpGauche();

    if (Robot::getpDroite() < 0)
        droite = -Robot::getpDroite();
    else
        droite = Robot::getpDroite();

    uint8_t gaucheUnite = gauche % 10;
    uint8_t gaucheDiz = (gauche - gaucheUnite) / 10;
    uint8_t droiteUnite = droite % 10;
    uint8_t droiteDiz = (droite - droiteUnite) / 10;

    switch (Robot::getAfficheur())
    {
    case 1:
        Robot::changerAfficheur();
        Robot::affiche(gaucheDiz);
        break;

    case 2:
        Robot::changerAfficheur();
        Robot::affiche(gaucheUnite);
        break;

    case 3:
        Robot::changerAfficheur();
        Robot::afficheTrait();
        break;

    case 4:
        Robot::changerAfficheur();
        Robot::affiche(droiteDiz);
        break;

    case 5:
        Robot::changerAfficheur();
        Robot::affiche(droiteUnite);
        Robot::setAfficheur(0);
        break;

    default:
        break;
    }
    Robot::incrementerAfficheur();
}

ISR(INT1_vect)
{
    float s1 = sonar.getDistance1();
    float s2 = sonar.getDistance2();
    float s3 = sonar.getDistance3();

    //Manoeuvre 1
    if (s1 >= 3 && s2 >= 3 && (s3 >= 1 && s3 < 3))
    {
        etatPresent = MANOEUVRE1;
    }
    //Manoeuvre 2
    else if ((s1 >= 1 && s1 < 3) && s2 >= 3 && s3 >= 3)
    {
        etatPresent = MANOEUVRE2;
    }
    //Manoeuvre 3
    else if (s1 >= 3 && s2 < 1 && s3 < 1)
    {
        etatPresent = MANOEUVRE3;
    }
    //Manoeuvre 4
    else if (s1 < 1 && s2 < 1 && s3 >= 3)
    {
        etatPresent = MANOEUVRE4;
    }
    //Manoeuvre 5
    else if (s1 < 1 && s2 < 1 && s3 < 1)
    {
        etatPresent = MANOEUVRE5;
    }
    //Manoeuvre 6
    else if ((s1 >= 1 && s1 < 3) && s2 >= 3 && (s3 >= 1 && s3 < 3))
    {
        etatPresent = MANOEUVRE6;
    }
    //Combinaison non reconnue
    else
    {
        etatPresent = MANOEUVREX;
    }
}
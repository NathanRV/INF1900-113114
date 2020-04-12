/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  main.cpp
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
Etats etatPresent = Etats::DETECTION;
LCM disp(&DDRB, &PORTB);
Robot robot;
Sonar sonar;

void static inline w(void)
{
    cp_wait_ms(2000);
}

// void controlerEtat(Etats etat)
// {
//     switch (etat)
//     {
//         case DETECTION:
//             initialiserDDR(ENTREE, SORTIE, ENTREE, ENTREE);
//             /**
//              * Les oscilloscopes ne doivent pas recevoir de signaux, 
//              * les DEL et les afficheurs 7 segments doivent être éteints.
//              */
//             //4 tours de boucle/seconde 1 tour = 0,25s
//             //Afficher distance et catégorie selon format
//             sonar.detecterObjets();

//             //Bouton-poussoir change mode manoeuvre si utilisateur satisfait
//             break;

//         case MANOEUVRE1:
//             initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
//             robot.activerAfficheur();
//             robot.minuterieAfficheur(0);
//             //Manoeuvre 1
//             robot.manoeuvre1();
//             etat = DETECTION;

//             break;

//         case MANOEUVRE2:
//             initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
//             robot.activerAfficheur();
//             robot.minuterieAfficheur(0);
//             //Manoeuvre 2
//             robot.manoeuvre2();
//             etat = DETECTION;
//             break;

//         case MANOEUVRE3:
//             initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
//             robot.activerAfficheur();
//             robot.minuterieAfficheur(0);
//             //Manoeuvre 3
//             robot.manoeuvre3();
//             etat = DETECTION;
//             break;

//         case MANOEUVRE4:
//             initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
//             robot.activerAfficheur();
//             robot.minuterieAfficheur(0);
//             //Manoeuvre 4
//             robot.manoeuvre4();
//             etat = DETECTION;
//             break;

//         case MANOEUVRE5:
//             initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
//             robot.activerAfficheur();
//             robot.minuterieAfficheur(0);
//             //Manoeuvre 5
//             robot.manoeuvre5();
//             etat = DETECTION;
//             break;

//         case MANOEUVRE6:
//             initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
//             robot.activerAfficheur();
//             robot.minuterieAfficheur(0);
//             //Manoeuvre 6
//             robot.manoeuvre6();
//             etat = DETECTION;
//             break;

//         case MANOEUVREX:
//             disp.clear();
//             disp << "Combinaison non evaluee";
//             attendre_ms(2000);
//             disp.clear();
//             etat = DETECTION;
//             break;
//     }
// }

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
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

enum Etats // Etats possibles
{
    DETECTION = 0,
    MANOEUVRE1,
    MANOEUVRE2,
    MANOEUVRE3,
    MANOEUVRE4,
    MANOEUVRE5,
    MANOEUVRE6,
    MANOEUVREX
};

//Variables Globales
Etats etatPresent = DETECTION;
LCM disp(&DDRB, &PORTB);
Sonar sonar;
int8_t pDroite = 0;
int8_t pGauche = 0;
int8_t afficheur = 1;

void static inline w(void)
{
    cp_wait_ms(2000);
}

// /**
//  * Manoeuvre 1 (OK - OK - ATTN)
//  * Vitesse initiale : (90, 90).
//  * La vitesse de la roue gauche descend graduellement jusqu'à 52, à raison de -1 par 100 ms.
//  * À (52, 90), on laisse passer 1000 ms.
//  * La vitesse de la roue gauche remonte graduellement jusqu'à 90, à raison de +1 par 100 ms.
//  * À (90, 90), on laisse passer 2000 ms.
//  * Fin de la manoeuvre.
//  */
// void manoeuvre1(LCM &disp)
// {
//     disp.clear();
//     disp << "Manoeuvre 1";
//     w();

//     for (int i = 90; i > 51; i--)
//     {
//         pGauche = i;
//         pDroite = 90;
//         ajusterPWM(pGauche, pDroite);
//         attendre_ms(100);
//     }

//     attendre_ms(900); //100 ms deja ecoules

//     for (int i = 52; i < 91; i++)
//     {
//         pGauche = i;
//         ajusterPWM(pGauche, pDroite);
//         attendre_ms(100);
//     }

//     attendre_ms(1900); //100 ms deja ecoules
//     arreterMoteur();
//     disp.clear();
// }

// /**
//  * Manoeuvre 2 (ATTN - OK - OK)
//  * Vitesse initiale : (90, 90).
//  * La vitesse de la roue droite descend graduellement jusqu'à 52, à raison de -1 par 100 ms.
//  * À (90, 52), on laisse passer 1000 ms.
//  * La vitesse de la roue droite remonte graduellement jusqu'à 90, à raison de +1 par 100 ms.
//  * À (90, 90), on laisse passer 2000 ms.
//  * Fin de la manoeuvre.
//  */
// void manoeuvre2(LCM &disp)
// {
//     disp.clear();
//     disp << "Manoeuvre 2";
//     w();

//     for (int i = 90; i > 51; i--)
//     {
//         pGauche = 90;
//         pDroite = i;
//         ajusterPWM(pGauche, pDroite);
//         attendre_ms(100);
//     }

//     attendre_ms(900); //100 ms deja ecoules

//     for (int i = 52; i < 91; i++)
//     {
//         pDroite = i;
//         ajusterPWM(pGauche, pDroite);
//         attendre_ms(100);
//     }

//     attendre_ms(1900); //100 ms deja ecoules
//     arreterMoteur();
//     disp.clear();
// }

// /**
//  * Manoeuvre 3 (OK - DNGR - DNGR)
//  * Vitesse initiale : (-50, 50). On laisse passer 1000 ms.
//  * On change la vitesse pour (66, 66) et on laisse passer 2000 ms.
//  * On change la vitesse pour (50, -50) et on laisse passer 1000 ms.
//  * On change la vitesse pour (78, 78) et on laisse passer 2000 ms.
//  * Fin de la manoeuvre.
//  */
// void manoeuvre3(LCM &disp)
// {
//     disp.clear();
//     disp << "Manoeuvre 3";
//     w();

//     pGauche = -50;
//     pDroite = 50;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(1000);

//     pGauche = 66;
//     pDroite = 66;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(2000);

//     pGauche = 50;
//     pDroite = -50;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(1000);

//     pGauche = 78;
//     pDroite = 78;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(2000);
//     arreterMoteur();
//     disp.clear();
// }

// /** Manoeuvre 4 (DNGR - DNGR - OK)
//  * Vitesse initiale : (50, -50). On laisse passer 1000 ms.
//  * On change la vitesse pour (66, 66) et on laisse passer 2000 ms.
//  * On change la vitesse pour (-50, 50) et on laisse passer 1000 ms.
//  * On change la vitesse pour (78, 78) et on laisse passer 2000 ms.
//  * Fin de la manoeuvre.
//  */
// void manoeuvre4(LCM &disp)
// {
//     disp.clear();
//     disp << "Manoeuvre 4";
//     w();

//     pGauche = 50;
//     pDroite = -50;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(1000);

//     pGauche = 66;
//     pDroite = 66;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(2000);

//     pGauche = -50;
//     pDroite = 50;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(1000);

//     pGauche = 78;
//     pDroite = 78;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(2000);
//     arreterMoteur();
//     disp.clear();
// }

// /** Manoeuvre 5 (DNGR - DNGR - DNGR)
//  * Vitesse initiale : (50, -50). On laisse passer 2000 ms.
//  * On change la vitesse pour (0, 0) et on passe à l'étape suivante.
//  * La vitesse monte graduellement de (0, 0) à (63, 63) à raison de +3 par 125 ms.
//  * À (63, 63), on laisse passer 2000 ms.
//  * Fin de la manoeuvre.
//  */
// void manoeuvre5(LCM &disp)
// {
//     disp.clear();
//     disp << "Manoeuvre 5";
//     w();

//     pGauche = 50;
//     pDroite = -50;
//     ajusterPWM(pGauche, pDroite);
//     attendre_ms(2000);

//     pGauche = 0;
//     pDroite = 0;
//     ajusterPWM(pGauche, pDroite);

//     for (int i = 0; i < 64; i += 3)
//     {
//         pGauche = i;
//         pDroite = i;
//         ajusterPWM(pGauche, pDroite);
//         attendre_ms(125);
//     }

//     attendre_ms(1875); //125 ms deja ecoules
//     arreterMoteur();
//     disp.clear();
// }

// /** Manoeuvre 6 (ATTN - OK - ATTN)
//  * Vitesse initiale : (90, 90).
//  * La vitesse descend graduellement de (90, 90) à (41, 41) à raison de -7 par 500 ms.
//  * À (41, 41), on laisse passer 2000 ms.
//  * Fin de la manoeuvre.
//  */
// void manoeuvre6(LCM &disp)
// {
//     disp.clear();
//     disp << "Manoeuvre 6";
//     w();
//     pGauche = 90;
//     pDroite = 90;
//     ajusterPWM(pGauche, pDroite);

//     for (int i = 90; i > 40; i -= 7)
//     {
//         pGauche = i;
//         pDroite = i;
//         ajusterPWM(pGauche, pDroite);
//         attendre_ms(500);
//     }

//     attendre_ms(1500); //500 ms deja ecoules
//     arreterMoteur();
//     disp.clear();
// }

/** 
 * Fonction permettant d'allumer la minuterie qui gere les afficheurs
 * @return void
*/
void minuterieAfficheur(uint8_t valeur)
{
    TCNT2 = 0; //compteur à 0

    //f=fréquence, N=facteur de prescaler
    //fOCnA=fclk/2N(1+OCRnX)

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)

    //OCR2B = valeur;
    //Output compare Register 1B correspond à D6 (OC2B)

    // division d'horloge par 8 - implique une frequence de PWM fixe

    //Voir p.152
    //TCCR2A |= (1 << WGM21) | (1 << COM2B1); //Table 16-4.
    //  COMnB0:Clear OCnB on Compare Match
    //  WGMn0:PWM, phase correct, 8-bit
    TCCR2B |= (1 << CS20) | (1 << CS21);
    //max prescaler of 32

    //Interruption comparaison OCIE2B
    TIMSK2 |= (1 << OCIE2B);
}

void afficheTrait()
{
    PORTC = 0b00000010;
    //changer pour constantes trait
}

void activerAfficheur()
{
    initialiserDDRA(SORTIE);
    initialiserDDRC(SORTIE);
    afficheur = 1;
    PORTA = 0b01111111;
}

void changerAfficheur()
{
    PORTA = PINA * 2;
    PORTA++;
    if (PINA == 0xFF)
    {
        PORTA = 0b11110111;
        //afficheur 1
    }
}

void affiche(uint8_t chiffre)
{
    switch (chiffre)
    {
    case 0:
        PORTC = 0b11111100;
        break;

    case 1:
        PORTC = 0b01100000;
        break;

    case 2:
        PORTC = 0b11011010;
        break;

    case 3:
        PORTC = 0b11110010;
        break;

    case 4:
        PORTC = 0b01100110;
        break;

    case 5:
        PORTC = 0b10110110;
        break;

    case 6:
        PORTC = 0b10111110;
        break;

    case 7:
        PORTC = 0b11100000;
        break;

    case 8:
        PORTC = 0b11111110;
        break;

    case 9:
        PORTC = 0b11110110;
        break;

    default:
        break;
    }
}

void initialisationBouton()
{
    cli();
    //Activer interruption bouton-poussoir
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC21);
    sei();
}

int main()
{
    initialisationBouton();
    Robot robot;

    for (;;)
    {
        switch (etatPresent)
        {
        case DETECTION:
            initialiserDDR(ENTREE, SORTIE, ENTREE, ENTREE);
            /**
             * Les oscilloscopes ne doivent pas recevoir de signaux, 
             * les DEL et les afficheurs 7 segments doivent être éteints.
             */
            //4 tours de boucle/seconde 1 tour = 0,25s
            //Afficher distance et catégorie selon format
            sonar.detecterObjets();

            //Bouton-poussoir change mode manoeuvre si utilisateur satisfait
            break;

        case MANOEUVRE1:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(0);
            //Manoeuvre 1
            robot.manoeuvre1();
            etatPresent = DETECTION;

            break;

        case MANOEUVRE2:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(0);
            //Manoeuvre 2
            robot.manoeuvre2();
            etatPresent = DETECTION;
            break;

        case MANOEUVRE3:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(0);
            //Manoeuvre 3
            robot.manoeuvre3();
            etatPresent = DETECTION;
            break;

        case MANOEUVRE4:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(0);
            //Manoeuvre 4
            robot.manoeuvre4();
            etatPresent = DETECTION;
            break;

        case MANOEUVRE5:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(0);
            //Manoeuvre 5
            robot.manoeuvre5();
            etatPresent = DETECTION;
            break;

        case MANOEUVRE6:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(0);
            //Manoeuvre 6
            robot.manoeuvre6();
            etatPresent = DETECTION;
            break;

        case MANOEUVREX:
            disp.clear();
            disp << "Combinaison non evaluee";
            attendre_ms(2000);
            disp.clear();
            etatPresent = DETECTION;
            break;
        }
    }

    return 0;
}

ISR(TIMER2_COMPB_vect)
{
    uint8_t gauche;
    uint8_t droite;

    if (pGauche < 0)
        gauche = -pGauche;
    else
        gauche = pGauche;

    if (pDroite < 0)
        droite = -pDroite;
    else
        droite = pDroite;

    uint8_t gaucheUnite = gauche % 10;
    uint8_t gaucheDiz = (gauche - gaucheUnite) / 10;
    uint8_t droiteUnite = droite % 10;
    uint8_t droiteDiz = (droite - droiteUnite) / 10;

    switch (afficheur)
    {
    case 1:
        changerAfficheur();
        affiche(gaucheDiz);
        break;

    case 2:
        changerAfficheur();
        affiche(gaucheUnite);
        break;

    case 3:
        changerAfficheur();
        afficheTrait();
        break;

    case 4:
        changerAfficheur();
        affiche(droiteDiz);
        break;

    case 5:
        changerAfficheur();
        affiche(droiteUnite);
        afficheur = 0;
        break;

    default:
        break;
    }
    afficheur++;
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
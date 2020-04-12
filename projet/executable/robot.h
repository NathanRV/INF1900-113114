#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
#include <stdlib.h>
#include "controleMoteur.h"
#include <avr/interrupt.h>
#include "constantes.h"
#include "delay.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
#include "sonar.h"

extern Sonar sonar;

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


class Robot
{
public:
    Robot();

    /**
     * Manoeuvre 1 (OK - OK - ATTN)
     * Vitesse initiale : (90, 90).
     * La vitesse de la roue gauche descend graduellement jusqu'à 52, à raison de -1 par 100 ms.
     * À (52, 90), on laisse passer 1000 ms.
     * La vitesse de la roue gauche remonte graduellement jusqu'à 90, à raison de +1 par 100 ms.
     * À (90, 90), on laisse passer 2000 ms.
     * Fin de la manoeuvre.
     */
    void manoeuvre1();

    /**
     * Manoeuvre 2 (ATTN - OK - OK)
     * Vitesse initiale : (90, 90).
     * La vitesse de la roue droite descend graduellement jusqu'à 52, à raison de -1 par 100 ms.
     * À (90, 52), on laisse passer 1000 ms.
     * La vitesse de la roue droite remonte graduellement jusqu'à 90, à raison de +1 par 100 ms.
     * À (90, 90), on laisse passer 2000 ms.
     * Fin de la manoeuvre.
     */
    void manoeuvre2();

    /**
     * Manoeuvre 3 (OK - DNGR - DNGR)
     * Vitesse initiale : (-50, 50). On laisse passer 1000 ms.
     * On change la vitesse pour (66, 66) et on laisse passer 2000 ms.
     * On change la vitesse pour (50, -50) et on laisse passer 1000 ms.
     * On change la vitesse pour (78, 78) et on laisse passer 2000 ms.
     * Fin de la manoeuvre.
     */
    void manoeuvre3();

    /** 
     * Manoeuvre 4 (DNGR - DNGR - OK)
     * Vitesse initiale : (50, -50). On laisse passer 1000 ms.
     * On change la vitesse pour (66, 66) et on laisse passer 2000 ms.
     * On change la vitesse pour (-50, 50) et on laisse passer 1000 ms.
     * On change la vitesse pour (78, 78) et on laisse passer 2000 ms.
     * Fin de la manoeuvre.
     */
    void manoeuvre4();

    /** Manoeuvre 5 (DNGR - DNGR - DNGR)
     * Vitesse initiale : (50, -50). On laisse passer 2000 ms.
     * On change la vitesse pour (0, 0) et on passe à l'étape suivante.
     * La vitesse monte graduellement de (0, 0) à (63, 63) à raison de +3 par 125 ms.
     * À (63, 63), on laisse passer 2000 ms.
     * Fin de la manoeuvre.
     */
    void manoeuvre5();

    /** Manoeuvre 6 (ATTN - OK - ATTN)
     * Vitesse initiale : (90, 90).
     * La vitesse descend graduellement de (90, 90) à (41, 41) à raison de -7 par 500 ms.
     * À (41, 41), on laisse passer 2000 ms.
     * Fin de la manoeuvre.
     */
    void manoeuvre6();

    /**
     * Fonction qui contrôle la machine à états du robot
     * @param in l'état présent
     * @return void
     */
    void controlerEtat(Etats& etat);

    /**
     * Fonction permettant d'allumer la minuterie qui gere les afficheurs
     * @return void
     */
    void minuterieAfficheur(uint8_t valeur);

    /**
     * Fonction qui affiche un trait sur
     * afficheur 7 segments
     */
    static void afficheTrait();

    /**
     * Fonction qui initialise les ports
     * et active 5ieme afficheur
     */
    void activerAfficheur();

    /**
     * Fonction qui change au prochain afficheur
     */
    static void changerAfficheur();

    /**
     * Fonction qui affiche le chiffre passee en parametre
     * @param uint8_t chiffre a afficher
     * @return void
     */
    static void affiche(uint8_t chiffre);


    /**
     * Getters des attributs statiques privés
     * @return l'attribut
     */
    static uint8_t getpGauche();
    static uint8_t getpDroite();
    static uint8_t getAfficheur();

    /**
     * Setter de l'attribut afficheur_
     * @param uint8_t chiffre a attribuer
     * @return void
     */
    static void setAfficheur(uint8_t afficheur);

    static void incrementerAfficheur();

private:
    static uint8_t pDroite_;
    static uint8_t pGauche_;
    static uint8_t afficheur_;
    LCM disp_;
};
#endif //ROBOT_H
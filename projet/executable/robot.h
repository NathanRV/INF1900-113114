
#include <stdio.h>
#include <stdlib.h>
#include "controleMoteur.h"
#include <avr/interrupt.h>
#include "constantes.h"
#include "delay.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

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

    // /**
    //  * Fonction permettant d'allumer la minuterie qui gere les afficheurs
    //  * @return void
    //  */
    // void minuterieAfficheur(uint8_t valeur);

    // /**
    //  * Fonction qui affiche un trait sur
    //  * afficheur 7 segments
    //  */
    // void afficheTrait();

    // /**
    //  * Fonction qui initialise les ports
    //  * et active 5ieme afficheur
    //  */
    // void activerAfficheur();

    // /**
    //  * Fonction qui change au prochain afficheur
    //  */
    // void changerAfficheur();

    // /**
    //  * Fonction qui affiche le chiffre passee en parametre
    //  * @param uint8_t chiffre a afficher
    //  * @return void
    //  */
    // void affiche(uint8_t chiffre);

private:
    int8_t pDroite = 0;
    int8_t pGauche = 0;
    uint8_t afficheur = 1;
    LCM disp;
};
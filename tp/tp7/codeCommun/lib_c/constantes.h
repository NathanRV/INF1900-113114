/*
    Date:       9-03-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  constantes.h
*/

#define F_CPU 8000000

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/**
 * Définition et déclaration des constantes utilisées
 * dans la librairie commune
 */

#define COULEUR_ROUGE     0x01
#define COULEUR_VERT      0x02
#define COULEUR_AUCUNE    0x00

/**
 * Définition de la valeur des entrées et des sorties
 * que peut prendre les PORTs
 */

#define ENTREE           0x00
#define SORTIE           0xff

/**
 * Définition des valeurs que peut prendre les décalages
 * de bits
 */

#define DECALAGE_1BIT 1
#define DECALAGE_2BIT 2
#define DECALAGE_3BIT 3
#define DECALAGE_4BIT 4
#define DECALAGE_5BIT 5
#define DECALAGE_6BIT 6
#define DECALAGE_7BIT 7

/**
 * Définition des intensités lumineuses 
 * Valeur entre 0 et 255
 */

#define SEUIL_LUMIERE_HAUTE 230
#define SEUIL_LUMIERE_BASSE 100

/**
 * Définition de la valeur du bouton d'interruption lorsqu'appuyé
 */
#define EST_APPUYE (PIND & 0x04)

/**
 * Definition des constantes pour la direction des roues
 */
 #define AVANCERGAUCHE     0b01
 #define RECULERGAUCHE     0b10
 #define AVANCERDROITE     0b00000100
 #define RECULERDROITE     0b10000000

 /**
 * Definition des constantes pour la classe Sonar
 */
#define LIMITE_COMPTEUR    58800
#define FACTEUR_CONVERSION 5800
#define PRECISION_NOMBRE   1
#define LARGEUR_NOMBRE     3

#define POSITION_SONAR1    0
#define POSITION_SONAR2    6
#define POSITION_SONAR3    12

#define DISTANCE_DNGR      1
#define DISTANCE_OK        3

 /**
 * Definition des constantes pour l'affichage 7 segments
 */
#define AFFICHE_TRAIT      0b00000010
#define AFFICHE0           0b11111100
#define AFFICHE1           0b01100000
#define AFFICHE2           0b11011010
#define AFFICHE3           0b11110010
#define AFFICHE4           0b01100110
#define AFFICHE5           0b10110110
#define AFFICHE6           0b10111110
#define AFFICHE7           0b11100000
#define AFFICHE8           0b11111110
#define AFFICHE9           0b11110110
#define INIT_AFFICHEUR     1
#define RESET              0
#define AFFICHEUR1         0b11110111
#define AFFICHEUR5         0b01111111

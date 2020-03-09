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
 #define AVANCER     0b1010
 #define RECULER     0b1111
 #define IMMOBILISER 0b0000

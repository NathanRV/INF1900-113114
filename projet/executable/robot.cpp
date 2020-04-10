#include "robot.h"


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
void Robot::manoeuvre1()
{
    disp.clear();
    disp << "Manoeuvre 1";
    w();

    for(int i = 90 ; i > 51 ; i--){
        pGauche = i;
        pDroite = 90;
        ajusterPWM(pGauche,pDroite);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for(int i = 52 ; i < 91 ; i++){
        pGauche = i;
        ajusterPWM(pGauche,pDroite);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    arreterMoteur();
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
void Robot::manoeuvre2()
{
    disp.clear();
    disp << "Manoeuvre 2";
    w();

    for(int i = 90 ; i > 51 ; i--){
        pGauche = 90;
        pDroite = i;
        ajusterPWM(pGauche,pDroite);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for(int i = 52 ; i < 91 ; i++){
        pDroite = i;
        ajusterPWM(pGauche,pDroite);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    arreterMoteur();
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
void Robot::manoeuvre3()
{
    disp.clear();
    disp << "Manoeuvre 3";
    w();

    pGauche = -50;
    pDroite = 50;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(1000);

    pGauche = 66;
    pDroite = 66;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(2000);

    pGauche = 50;
    pDroite = -50;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(1000);

    pGauche = 78;
    pDroite = 78;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(2000);
    arreterMoteur();
    disp.clear();
}

/** 
 * Manoeuvre 4 (DNGR - DNGR - OK)
 * Vitesse initiale : (50, -50). On laisse passer 1000 ms.
 * On change la vitesse pour (66, 66) et on laisse passer 2000 ms.
 * On change la vitesse pour (-50, 50) et on laisse passer 1000 ms.
 * On change la vitesse pour (78, 78) et on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void Robot::manoeuvre4()
{
    disp.clear();
    disp << "Manoeuvre 4";
    w();

    pGauche = 50;
    pDroite = -50;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(1000);

    pGauche = 66;
    pDroite = 66;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(2000);

    pGauche = -50;
    pDroite = 50;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(1000);

    pGauche = 78;
    pDroite = 78;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(2000);
    arreterMoteur();
    disp.clear();
}

/** Manoeuvre 5 (DNGR - DNGR - DNGR)
 * Vitesse initiale : (50, -50). On laisse passer 2000 ms.
 * On change la vitesse pour (0, 0) et on passe à l'étape suivante.
 * La vitesse monte graduellement de (0, 0) à (63, 63) à raison de +3 par 125 ms.
 * À (63, 63), on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void Robot::manoeuvre5()
{
    disp.clear();
    disp << "Manoeuvre 5";
    w();

    pGauche = 50;
    pDroite = -50;
    ajusterPWM(pGauche,pDroite);
    attendre_ms(2000);

    pGauche = 0;
    pDroite = 0;
    ajusterPWM(pGauche,pDroite);

    for (int i = 0; i < 64; i += 3)
    {
        pGauche = i;
        pDroite = i;
        ajusterPWM(pGauche,pDroite);
        attendre_ms(125);
    }

    attendre_ms(1875); //125 ms deja ecoules
    arreterMoteur();
    disp.clear();
}

/** Manoeuvre 6 (ATTN - OK - ATTN)
 * Vitesse initiale : (90, 90).
 * La vitesse descend graduellement de (90, 90) à (41, 41) à raison de -7 par 500 ms.
 * À (41, 41), on laisse passer 2000 ms.
 * Fin de la manoeuvre.
 */
void Robot::manoeuvre6()
{
    disp.clear();
    disp << "Manoeuvre 6";
    w();
    pGauche = 90;
    pDroite = 90;
    ajusterPWM(pGauche,pDroite);

    for (int i = 90; i > 40; i -= 7)
    {
        pGauche = i;
        pDroite = i;
        ajusterPWM(pGauche,pDroite);
        attendre_ms(500);
    }

    attendre_ms(1500); //500 ms deja ecoules
    arreterMoteur();
    disp.clear();
}

/** 
 * Fonction permettant d'allumer la minuterie qui gere les afficheurs
 * @return void
*/
void Robot::minuterieAfficheur(uint8_t valeur){
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
    TCCR2B |= (1 << CS20) | (1 << CS21) ; 
    //max prescaler of 32

    //Interruption comparaison OCIE2B
    TIMSK2 |= (1 << OCIE2B);
}

/**
 * Fonction qui affiche un trait sur
 * afficheur 7 segments
 */
void Robot::afficheTrait(){
    PORTC = 0b00000010;
    //changer pour constantes trait
}

/**
 * Fonction qui initialise les ports
 * et active 5ieme afficheur
 */
void Robot::activerAfficheur(){
    initialiserDDRA(SORTIE);
    initialiserDDRC(SORTIE);
    afficheur = 1;
    PORTA = 0b01111111;
}

/**
 * Fonction qui change au prochain afficheur
 */
void Robot::changerAfficheur(){
    PORTA = PINA * 2;
    PORTA ++;
    if(PINA == 0xFF){
        PORTA = 0b11110111; 
        //afficheur 1
    }
}

/**
 * Fonction qui affiche le chiffre passee en parametre
 * @param uint8_t chiffre a afficher
 * @return void
 */
void Robot::affiche(uint8_t chiffre){
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

Robot::ISR(TIMER2_COMPB_vect){
    uint8_t gauche;
    uint8_t droite;
    
    if(pGauche < 0)
        gauche = -pGauche;
    else
        gauche = pGauche;
    
    
    if(pDroite < 0)
        droite = -pDroite;
    else
        droite = pDroite;


    uint8_t gaucheUnite = gauche % 10;
    uint8_t gaucheDiz = (gauche - gaucheUnite)/10;
    uint8_t droiteUnite = droite % 10;
    uint8_t droiteDiz = (droite - droiteUnite)/10;
    
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
    afficheur ++;
}


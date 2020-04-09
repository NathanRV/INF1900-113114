

#include "7segments.h"
/**
 * 0 : dot
 * 1 : middle
 * 2 : upper left
 * 3 : lower left
 * 4 : lower centre
 * 5 : lower right
 * 6 : upper right
 * 7 : upper centre
 * Suggestion : utilisez Timer/Counter2 pour réaliser cette fonctionnalité. 
 * Plus particulièrement,ajuster les registres nécessaires et ensuite 
 * placer votre code dans la fonction
 * ISR(TIMER2_COMPB_vect).
 * 
 * En mode détection, les oscilloscopes ne doivent pas recevoir de signaux, 
 * les DEL et les afficheurs 7 segments doivent être éteints.
 * 
 * Les afficheurs 7 segments affiche puissance des roues.
 */

/** 
 * Fonction permettant d'allumer la minuterie qui gere les afficheurs
 * @return void
*/
void minuterieAfficheur(uint8_t valeur){
	TCNT2 = 0; //compteur à 0

	//f=fréquence, N=facteur de prescaler
	//fOCnA=fclk/2N(1+OCRnX)

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)
    
    OCR2B = valeur;
    //Output compare Register 1B correspond à D6 (OC2B)
    
    // division d'horloge par 8 - implique une frequence de PWM fixe

    //Voir p.123 & section 16.10.4
    TCCR2A |= (1 << WGM20) | (1 << COM2A1) | (1 << COM2B1); //Table 16-4.
    //  COM1A1&COM1B1:Clear OCnA/OCnB on Compare Match when up-counting. 
    //  Set OCnA/OCnB on Compare Match when downcounting.
    //  WGM10:PWM, phase correct, 8-bit
    TCCR2B |= (1 << CS21); //prescaler 8

}

void afficheTrait(){
    PORTC = 0b00000010;
}

void activerAfficheur(){
    initialiserDDRA(SORTIE);
    initialiserDDRC(SORTIE);
    PORTA=0b11110111;
}

void changerAfficheur(){
    attendre_ms(10);
    PORTA = PINA * 2;
    //PORTA = PINA << 1;
    PORTA ++;
    if(PINA == 0xFF){
        afficheur1();
    }
}

void affichage(uint8_t gauche, uint8_t droite){
    uint8_t gaucheUnite = gauche % 10;
    uint8_t gaucheDiz = (gauche - gaucheUnite)/10;
    uint8_t droiteUnite = droite % 10;
    uint8_t droiteDiz = (droite - droiteUnite)/10;
    affiche(gaucheDiz);
    changerAfficheur();
    affiche(gaucheUnite);
    changerAfficheur();
    afficheTrait();
    changerAfficheur();
    affiche(droiteDiz);
    changerAfficheur();
    affiche(droiteUnite);
    changerAfficheur();
}


void affiche(uint8_t chiffre){
    chiffre = chiffre % 10;

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
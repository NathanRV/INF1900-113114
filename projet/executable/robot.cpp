/*
    Date:       11-04-2020
    Authors:    David Saikali,          2015144
                Nathan Ramsay-Vejlens,  1989944
                Agnes Sam Yue Chi,      1954192
                Jefferson Lam,          1963528
    File name:  robot.cpp
*/

#include "robot.h"

int8_t Robot::pDroite_ = 0;
int8_t Robot::pGauche_ = 0;
uint8_t Robot::afficheur_ = INIT_AFFICHEUR;

Robot::Robot() : disp_(&DDRB, &PORTB) {}

void Robot::manoeuvre1()
{
    disp_.clear();
    disp_ << "Manoeuvre 1";
    attendre_ms(2000);

    for (int i = 90; i > 51; i--)
    {
        setPourcentage(i, 90);
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for (int i = 52; i < 91; i++)
    {
        setPourcentage(i, 90);
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    setPourcentage(0, 0);
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre2()
{
    disp_.clear();
    disp_ << "Manoeuvre 2";
    attendre_ms(2000);

    for (int i = 90; i > 51; i--)
    {
        setPourcentage(90, i);
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for (int i = 52; i < 91; i++)
    {
        setPourcentage(90, i);
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    setPourcentage(0, 0);
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre3()
{
    disp_.clear();
    disp_ << "Manoeuvre 3";
    attendre_ms(2000);

    setPourcentage(-50, 50);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    setPourcentage(66, 66);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);

    setPourcentage(50, -50);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    setPourcentage(78, 78);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);
    setPourcentage(0, 0);
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre4()
{
    disp_.clear();
    disp_ << "Manoeuvre 4";
    attendre_ms(2000);

    setPourcentage(50, -50);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    setPourcentage(66, 66);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);

    setPourcentage(-50, 50);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    setPourcentage(78, 78);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);
    setPourcentage(0, 0);
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre5()
{
    disp_.clear();
    disp_ << "Manoeuvre 5";
    attendre_ms(2000);


    setPourcentage(50, -50);
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);

    setPourcentage(0, 0);
    arreterMoteur();

    for (int i = 0; i < 64; i += 3)
    {
        setPourcentage(i, i);
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(125);
    }

    attendre_ms(1875); //125 ms deja ecoules
    setPourcentage(0, 0);
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre6()
{
    disp_.clear();
    disp_ << "Manoeuvre 6";
    attendre_ms(2000);
    setPourcentage(90, 90);
    ajusterPWM(pGauche_, pDroite_);
    for (int i = 90; i > 40; i -= 7)
    {
        pGauche_ = i;
        pDroite_ = i;
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(500);
    }
    attendre_ms(1500); //500 ms deja ecoules
    setPourcentage(0, 0);
    arreterMoteur();
    disp_.clear();
}

void Robot::controlerEtat(Etats& etat)
{
    switch (etat)
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
            minuterieAfficheur(RESET);
            //Manoeuvre 1
            manoeuvre1();
            etat = Etats::DETECTION;
            break;

        case MANOEUVRE2:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(RESET);
            //Manoeuvre 2
            manoeuvre2();
            etat = Etats::DETECTION;
            break;

        case MANOEUVRE3:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(RESET);
            //Manoeuvre 3
            manoeuvre3();
            etat = Etats::DETECTION;
            break;

        case MANOEUVRE4:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(RESET);
            //Manoeuvre 4
            manoeuvre4();
            etat = Etats::DETECTION;
            break;

        case MANOEUVRE5:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(RESET);
            //Manoeuvre 5
            manoeuvre5();
            etat = Etats::DETECTION;
            break;

        case MANOEUVRE6:
            initialisationInterruption(SORTIE, SORTIE, SORTIE, SORTIE);
            activerAfficheur();
            minuterieAfficheur(RESET);
            //Manoeuvre 6
            manoeuvre6();
            etat = Etats::DETECTION;
            break;

        case MANOEUVREX:
            disp_.clear();
            disp_ << "Combinaison non evaluee";
            attendre_ms(2000);
            disp_.clear();
            etat = Etats::DETECTION;
            break;
    }
}


void Robot::minuterieAfficheur(uint8_t valeur)
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

void Robot::afficheTrait()
{
    PORTC = AFFICHE_TRAIT;
}

void Robot::activerAfficheur()
{
    initialiserDDRA(SORTIE);
    initialiserDDRC(SORTIE);
    setAfficheur(INIT_AFFICHEUR);
    PORTA = AFFICHEUR5;
}

void Robot::changerAfficheur()
{
    PORTA = PINA * 2;
    PORTA++;
    if (PINA == 0xFF)
    {
        PORTA = AFFICHEUR1;
        //afficheur 1
    }
}

void Robot::affiche(uint8_t chiffre)
{
    switch (chiffre)
    {
    case 0:
        PORTC = AFFICHE0;
        break;

    case 1:
        PORTC = AFFICHE1;
        break;

    case 2:
        PORTC = AFFICHE2;
        break;

    case 3:
        PORTC = AFFICHE3;
        break;

    case 4:
        PORTC = AFFICHE4;
        break;

    case 5:
        PORTC = AFFICHE5;
        break;

    case 6:
        PORTC = AFFICHE6;
        break;

    case 7:
        PORTC = AFFICHE7;
        break;

    case 8:
        PORTC = AFFICHE8;
        break;

    case 9:
        PORTC = AFFICHE9;
        break;

    default:
        break;
    }
}

int8_t Robot::getpGauche()
{
    return pGauche_;
}

int8_t Robot::getpDroite()
{
    return pDroite_;
}

uint8_t Robot::getAfficheur()
{
    return afficheur_;
}

void Robot::setPourcentage(int8_t pGauche, int8_t pDroite)
{
    pGauche_ = pGauche;
    pDroite_ = pDroite;
}

void Robot::setAfficheur(uint8_t afficheur)
{
    afficheur_ = afficheur;
}

void Robot::incrementerAfficheur()
{
    afficheur_++;
}
#include "robot.h"

Robot::Robot() : disp(&DDRB, &PORTB) {}

void Robot::manoeuvre1()
{
    disp.clear();
    disp << "Manoeuvre 1";
    attendre_ms(2000);

    for (int i = 90; i > 51; i--)
    {
        pGauche = i;
        pDroite = 90;
        ajusterPWM(pGauche, pDroite);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for (int i = 52; i < 91; i++)
    {
        pGauche = i;
        ajusterPWM(pGauche, pDroite);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    arreterMoteur();
    disp.clear();
}

void Robot::manoeuvre2()
{
    disp.clear();
    disp << "Manoeuvre 2";
    attendre_ms(2000);

    for (int i = 90; i > 51; i--)
    {
        pGauche = 90;
        pDroite = i;
        ajusterPWM(pGauche, pDroite);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for (int i = 52; i < 91; i++)
    {
        pDroite = i;
        ajusterPWM(pGauche, pDroite);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    arreterMoteur();
    disp.clear();
}

void Robot::manoeuvre3()
{
    disp.clear();
    disp << "Manoeuvre 3";
    attendre_ms(2000);

    pGauche = -50;
    pDroite = 50;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(1000);

    pGauche = 66;
    pDroite = 66;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(2000);

    pGauche = 50;
    pDroite = -50;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(1000);

    pGauche = 78;
    pDroite = 78;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(2000);
    arreterMoteur();
    disp.clear();
}

void Robot::manoeuvre4()
{
    disp.clear();
    disp << "Manoeuvre 4";
    attendre_ms(2000);

    pGauche = 50;
    pDroite = -50;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(1000);

    pGauche = 66;
    pDroite = 66;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(2000);

    pGauche = -50;
    pDroite = 50;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(1000);

    pGauche = 78;
    pDroite = 78;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(2000);
    arreterMoteur();
    disp.clear();
}

void Robot::manoeuvre5()
{
    disp.clear();
    disp << "Manoeuvre 5";
    attendre_ms(2000);

    pGauche = 50;
    pDroite = -50;
    ajusterPWM(pGauche, pDroite);
    attendre_ms(2000);

    pGauche = 0;
    pDroite = 0;
    ajusterPWM(pGauche, pDroite);

    for (int i = 0; i < 64; i += 3)
    {
        pGauche = i;
        pDroite = i;
        ajusterPWM(pGauche, pDroite);
        attendre_ms(125);
    }

    attendre_ms(1875); //125 ms deja ecoules
    arreterMoteur();
    disp.clear();
}

void Robot::manoeuvre6()
{
    disp.clear();
    disp << "Manoeuvre 6";
    attendre_ms(2000);
    pGauche = 90;
    pDroite = 90;
    ajusterPWM(pGauche, pDroite);
    for (int i = 90; i > 40; i -= 7)
    {
        pGauche = i;
        pDroite = i;
        ajusterPWM(pGauche, pDroite);
        attendre_ms(500);
    }
    attendre_ms(1500); //500 ms deja ecoules
    arreterMoteur();
    disp.clear();
}

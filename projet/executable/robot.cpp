#include "robot.h"

uint8_t Robot::pDroite_ = 0;

Robot::Robot() : disp_(&DDRB, &PORTB) {}

void Robot::manoeuvre1()
{
    disp_.clear();
    disp_ << "Manoeuvre 1";
    attendre_ms(2000);

    for (int i = 90; i > 51; i--)
    {
        pGauche_ = i;
        pDroite_ = 90;
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for (int i = 52; i < 91; i++)
    {
        pGauche_ = i;
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
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
        pGauche_ = 90;
        pDroite_ = i;
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(900); //100 ms deja ecoules

    for (int i = 52; i < 91; i++)
    {
        pDroite_ = i;
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(100);
    }

    attendre_ms(1900); //100 ms deja ecoules
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre3()
{
    disp_.clear();
    disp_ << "Manoeuvre 3";
    attendre_ms(2000);

    pGauche_ = -50;
    pDroite_ = 50;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    pGauche_ = 66;
    pDroite_ = 66;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);

    pGauche_ = 50;
    pDroite_ = -50;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    pGauche_ = 78;
    pDroite_ = 78;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre4()
{
    disp_.clear();
    disp_ << "Manoeuvre 4";
    attendre_ms(2000);

    pGauche_ = 50;
    pDroite_ = -50;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    pGauche_ = 66;
    pDroite_ = 66;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);

    pGauche_ = -50;
    pDroite_ = 50;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(1000);

    pGauche_ = 78;
    pDroite_ = 78;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre5()
{
    disp_.clear();
    disp_ << "Manoeuvre 5";
    attendre_ms(2000);

    pGauche_ = 50;
    pDroite_ = -50;
    ajusterPWM(pGauche_, pDroite_);
    attendre_ms(2000);

    pGauche_ = 0;
    pDroite_ = 0;
    ajusterPWM(pGauche_, pDroite_);

    for (int i = 0; i < 64; i += 3)
    {
        pGauche_ = i;
        pDroite_ = i;
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(125);
    }

    attendre_ms(1875); //125 ms deja ecoules
    arreterMoteur();
    disp_.clear();
}

void Robot::manoeuvre6()
{
    disp_.clear();
    disp_ << "Manoeuvre 6";
    attendre_ms(2000);
    pGauche_ = 90;
    pDroite_ = 90;
    ajusterPWM(pGauche_, pDroite_);
    for (int i = 90; i > 40; i -= 7)
    {
        pGauche_ = i;
        pDroite_ = i;
        ajusterPWM(pGauche_, pDroite_);
        attendre_ms(500);
    }
    attendre_ms(1500); //500 ms deja ecoules
    arreterMoteur();
    disp_.clear();
}
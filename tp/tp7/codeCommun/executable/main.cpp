#include "controleDEL.h"
#include "controleMoteur.h"
#include "capteurs.h"
#include "can.h"
#include "initialisation.h"
#include "constantes.h"
#include "delay.h"
#include "interactionUART.h"
#include "antirebond.h"

int main() {
    initialiserDDRB(SORTIE);
    initialiserDDRD(ENTREE);
    boutonAntiRebond();
    Memoire24CXXX memoire;
    transmissionUART(250);
    controlerLumiereSelonIntensite(COULEUR_ROUGE, COULEUR_VERT);
}
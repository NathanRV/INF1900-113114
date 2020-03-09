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
<<<<<<< HEAD
    boutonAntiRebond();
    Memoire24CXXX memoire;
    transmissionUART(250);
    controlerLumiereSelonIntensite(COULEUR_ROUGE, COULEUR_VERT);
=======
    couleurAmbre(10000);
>>>>>>> fcd91e98f5df9aa20140f0981ac95b243ff72ad9
}
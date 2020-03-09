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
    couleurAmbre(10000);
=======
>>>>>>> 0e365d630d286cb4b4a39161db4f7932b4b36815
}
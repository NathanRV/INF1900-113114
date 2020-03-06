#include "controleDEL.h"
#include "controleMoteur.h"
#include "capteurs.h"
#include "can.h"
#include "initialisation.h"
#include "constantes.h"

int main() {
    initialiserDDRB(SORTIE);
    initialiserDDRD(ENTREE);

    couleurAmbre();
}
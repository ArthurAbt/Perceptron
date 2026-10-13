#include <stdio.h>

#include "donnees.h"
#include "perceptron.h"

int main() {
    float longueur_sepale[150], largeur_sepale[150], longueur_petale[150], largeur_petale[150]; // Les données d'entrées
    int famille[150];   // Rempli par des 0, 1, 2, respectivement les famille 0, 1 et 2 (50 premiers sont de la famille 0,les 50 suivant de la famille 1 et les 50 derniers de a famille)

    /* Lire_donnes et normalise_tout pas utile pour la preparation, mais pour la seance 1 oui*/       
    lire_donnees(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille); // Permet d'extraire toute les données du tableau datairis.csv et de les stocker dans les differnetes listes
    normalise_tout(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale); // Normalise toute nos valeurs (qui le sont deja pour celles de test)

validation_jeux_donnees(15, jeux_test_lineaire, famille);

return 0;
}
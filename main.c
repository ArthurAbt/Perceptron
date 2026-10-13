#include <stdio.h>
#include <signal.h>

#include "donnees.h"
#include "perceptron.h"
#include "orchestrateur.h"

int main() {
    double longueur_sepale[150], largeur_sepale[150], longueur_petale[150], largeur_petale[150]; // 4 tableaux de 150 doubles qui seront ensuite rempis avec les caractéristiques des données d'entrées
    int famille[150];   // Rempli par des 0, 1, 2, respectivement les famille 0, 1 et 2 . Dans data_Iris.csv, (50 premiers sont de la famille 0,les 50 suivant de la famille 1 et les 50 derniers de a famille)
    
    executer_systeme_ipc(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille);

return 0;
}
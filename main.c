#include <stdio.h>

#include "donnees.h"
#include "perceptron.h"

int main() {
    float longueur_sepale[150], largeur_sepale[150], longueur_petale[150], largeur_petale[150]; // Les données d'entrées
    int famille[150];   // Rempli par des 0, 1, 2, respectivement les famille 0, 1 et 2 (50 premiers sont de la famille 0,les 50 suivant de la famille 1 et les 50 derniers de a famille)

    double jeux_test_lineaire[NB_data][4] = {       // vecteurs de test linearisés (donné par le prof)
        {-0.613472, 0.192301, -4.148675, -0.758351},
        {-0.778532, -0.024905, -4.148675, -0.758351},
        {-0.943593, 0.061977, -4.324615, -0.758351},
        {-1.026123, 0.018536, -3.972734, -0.758351},
        {-0.696002, 0.235742, -4.148675, -0.682465},
        {0.954602, 0.061977, 1.657359, 0.152280},
        {0.459421, 0.061977, 1.305478, 0.228166},
        {0.872072, 0.018536, 2.009239, 0.228166},
        {-0.283351, -0.328992, 0.425776, 0.076394},
        {0.541951, -0.111787, 1.481418, 0.228166},
        {0.376891, 0.105419, 3.944584, 0.987025},
        {-0.035760, -0.155228, 2.361120, 0.531710},
        {1.037132, -0.024905, 3.768643, 0.683482},
        {0.376891, -0.068346, 3.240822, 0.455824},
        {0.541951, -0.024905, 3.592703, 0.759367}
    };

int sortie_attendue[NB_data] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};   // Sories attendues pour les NB_data vecteurs de test

 /* Lire_donnes et normalise_tout pas utile pour la preparation, mais pour la seance 1 oui*/       
lire_donnees(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille); // Permet d'extraire toute les données du tableau datairis.csv et de les stocker dans les differnetes listes
normalise_tout(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale); // Normalise toute nos valeurs (qui le sont deja pour celles de test)

validation_jeux_donnees(15, jeux_test_lineaire, famille);

return 0;
}
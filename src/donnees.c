#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "donnees.h"

void lire_donnees(float longueur_sepale[150], float largeur_sepale[150], float longueur_petale[150], float largeur_petale[150], int famille[150]) {
    FILE *fichier;
    char buffer[100];
    int i = 0;

    fichier = fopen("data_iris.csv", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture de data_iris.csv !\n");
        return;
    }
    else {
        while (fgets(buffer, 100, fichier) != NULL) {    // Lit toute les lignes et stock jusqu'à 100 caractères dans buffer, renvoie NULL lorsqu'on arrive à la fin du fichier
            sscanf(buffer, "%f;%f;%f;%f;%d", &longueur_sepale[i], &largeur_sepale[i], &longueur_petale[i], &largeur_petale[i], &famille[i]);   // Stock chaque donnée dans son tableau respectif
            i++;
        }
        fclose(fichier);
    }
}

float moyenne(float donnees[150]) {
    int i;
    float somme = 0.0;

    for (i = 0; i < 150; i++) {
        somme += donnees[i];
    }
    return somme / 150.0;
}

float ecart_type(float donnees[150]){
    float m = moyenne(donnees), somme = 0.0;
    int i;

    for (i = 0; i < 150; i++) {
        somme += pow(donnees[i] - m, 2);    // fonction puissance de <math.h>
    }
    return sqrt(somme / 150.0);
}

void normalise(float donnees[150]) {
    int i;
    float m = moyenne(donnees), e = ecart_type(donnees);
    for (i = 0; i < 150; i++) {
        donnees[i] = (donnees[i] - m) * e;
    }
    return;
}

void normalise_tout(float longueur_sepale[150], float largeur_sepale[150], float longueur_petale[150], float largeur_petale[150]) {
    normalise(longueur_sepale);
    normalise(largeur_sepale);
    normalise(longueur_petale);
    normalise(largeur_petale);
    return;
}
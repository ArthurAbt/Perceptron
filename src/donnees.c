#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "donnees.h"
#include "perceptron.h"

void lire_donnees(float longueur_sepale[150], float largeur_sepale[150], float longueur_petale[150], float largeur_petale[150], int famille[150]) {
    FILE *fichier;
    int i=0;
    int retour_scanf;
    fichier = fopen("data_iris.csv", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture de data_iris.csv !\n");
        return;
    }
    else {
        while ( (retour_scanf = fscanf(fichier, "%f;%f;%f;%f;%d", &longueur_sepale[i], &largeur_sepale[i], &longueur_petale[i], &largeur_petale[i], &famille[i]) )  != EOF) // fscanf renvoie le nombre d'affectation qu'elle a reussit a faire. S'il y en a moins que 5, c'est qu'il ya un prblm, ou qu'on est a la fin du ficher 
        {
            if (retour_scanf == 5) {
                i++;
            } else {
                printf("Erreur de format rencontrée à la ligne %d.\n", i + 1);
                break; 
            }
        } 
    }
    fclose(fichier);
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

void valdation_1_donnee(double fleur[4], double resultats[2]) {
    double coef_MAT1[TAILLE_entree+1][NB_neurones_C1] = {
		{ +1.70, +2.58, -1.87}, 
		{+1.56, +4.04, -5.81}, 
		{-2.68, -3.84, +4.21}, 
		{-0.02, -6.49, +6.97}, 
		{-4.07, +7.31, -8.16}
    };
			
    double coef_MAT2[NB_neurones_C1+1][NB_neurones_C2] = {
		{ +9.00, -10.75, -1.38},
		{-1.12, +4.68, -5.82}, 
		{-3.43, -5.32, +5.60}, 
		{-3.30, +1.42, -1.22 }
    };

    prediction(fleur, coef_MAT1, coef_MAT2, resultats); // Cette fonction met les biais au bon endroit et donne pour chaque neurone le bon coeff. Elle prends aussi en parametres les entrées de la fleur. Surement a reecrire vu que nos données ne sont pas tous au meme endroit.
}

void validation_jeux_donnees(int nb_fleurs, double donnees[][4], int famille[]) {
    int i;

    for (i = 0; i < nb_fleurs; i++) {
        double resultats[2];

        valdation_1_donnee(donnees[i], resultats);
        famille[i] = (int) resultats[0];
        printf("%d | ", famille[i]);
    }
    printf("\n");
}
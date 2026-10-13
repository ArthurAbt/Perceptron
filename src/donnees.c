#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "donnees.h"
#include "perceptron.h"

void lire_donnees(double longueur_sepale[150], double largeur_sepale[150], double longueur_petale[150], double largeur_petale[150], double famille[150]) {
    FILE *fichier;
    int i=0;
    int retour_scanf;
    fichier = fopen("data_iris.csv", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture de data_iris.csv !\n");
        return;
    }
    else {
        while ( (retour_scanf = fscanf(fichier, "%lf;%lf;%lf;%lf;%lf", &longueur_sepale[i], &largeur_sepale[i], &longueur_petale[i], &largeur_petale[i], &famille[i]) )  != EOF) // fscanf renvoie le nombre d'affectation qu'elle a reussit a faire. S'il y en a moins que 5, c'est qu'il ya un prblm, ou qu'on est a la fin du ficher 
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

float moyenne(double donnees[150]) {
    int i;
    float somme = 0.0;

    for (i = 0; i < 150; i++) {
        somme += donnees[i];
    }
    return somme / 150.0;
}

float ecart_type(double donnees[150]){
    float m = moyenne(donnees), somme = 0.0;
    int i;

    for (i = 0; i < 150; i++) {
        somme += pow(donnees[i] - m, 2);    // fonction puissance de <math.h>
    }
    return sqrt(somme / 150.0);
}

void normalise(double donnees[150]) {
    int i;
    float m = moyenne(donnees), e = ecart_type(donnees);
    for (i = 0; i < 150; i++) {
        donnees[i] = (donnees[i] - m) * e;
    }
    return;
}

void normalise_tout(double longueur_sepale[150], double largeur_sepale[150], double longueur_petale[150], double largeur_petale[150]) {
    normalise(longueur_sepale);
    normalise(largeur_sepale);
    normalise(longueur_petale);
    normalise(largeur_petale);
    return;
}

void validation_1_donnee(double fleur[4], double resultats[3]) {
    double coef_MAT1[TAILLE_entree+1][NB_neurones_C1] = {
		{ +1.703661357392334, +2.763631108685933, -2.17236310620485}, 
		{+1.560385693578073, +3.973334575425574, -5.687438139503607}, 
		{-2.681166224391079, -3.131516653284507, +3.143949358790173}, 
		{-0.02639163020174042, -6.500059250638189, +7.00651555282157}, 
		{-4.077513418151064, +7.565128560821631, -8.505618677932459}
    };
			
    double coef_MAT2[NB_neurones_C1+1][NB_neurones_C2] = {
		{ +9.001713871164204, -10.52803062971971, -1.602240268200863},
		{-1.12770505333443, +4.930756962081604, -6.057546672046951}, 
		{-3.42697126393812, -5.601264307780169, +5.878238858982915}, 
		{-3.31644629415654, +1.215105079193245, -1.007589578200665 }
    };

    prediction(fleur, coef_MAT1, coef_MAT2, resultats); // Cette fonction met les biais au bon endroit et donne pour chaque neurone le bon coeff. Elle prends aussi en parametres les entrées de la fleur. Surement a reecrire vu que nos données ne sont pas tous au meme endroit.
}

void validation_jeux_donnees(int nb_fleurs, double donnees[][4], double famille[]) {
    int i;

    for (i = 0; i < nb_fleurs; i++) {
        double resultats[2];

        validation_1_donnee(donnees[i], resultats);
        famille[i] = (int) resultats[0];
        printf("%lf | ", famille[i]);
    }
    printf("\n");
}
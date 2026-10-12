#include <stdio.h>
#include <math.h>

#include "perceptron.h"

/*  nb est la taille des vecteurs d'entree et de sortie - in et out. Fonction récupérer du prof */
void softmax(const double in[], double out[], int nb) {
    /* Trouver la valeur max pour la stabilité numérique */
    double max_softmax = in[0];
    for (int l = 1; l < nb; l++) {
        if (in[l] > max_softmax)
				max_softmax = in[l];
    }

    /* Calculer exp(x - max) */
    double somme = 0.0;
    for (int l = 0; l < nb; l++) {
        out[l] = exp(in[l] - max_softmax);
        somme += out[l];
    }

    /* Normaliser */
    for (int l = 0; l < nb; l++) {
        out[l] /= somme;
    }
}


/* Fonction d'activation tanh */
double act_tanh(double x) {
    return tanh(x);
}

void prediction(double fleur[4], double coef_MAT1[TAILLE_entree+1][NB_neurones_C1], double coef_MAT2[NB_neurones_C1+1][NB_neurones_C2], double predictions[3]) {
    double sortie_couche1[NB_neurones_C1], pre_softmax[NB_neurones_C2], somme;
    int i, j;

    for (i = 0; i < NB_neurones_C1; i++) {  // parcours les neurones de C1, stock leur sorties dans sorties_couche1
        somme = coef_MAT1[TAILLE_entree][i];    // Initialise les biais de chaque neurone
        for (j = 0; j < TAILLE_entree; j++) {
            somme += fleur[j] * coef_MAT1[j][i];
        }
        sortie_couche1[i] = act_tanh(somme);
    }
    for (i = 0; i < NB_neurones_C2; i++) {  // parcours les neurones de C2, stock leur sorties dans pre_softmax (sortie de la couche 2)
        somme = coef_MAT2[NB_neurones_C1][i];
        for (j = 0; j < NB_neurones_C1; j++) {
            somme += sortie_couche1[j] * coef_MAT2[j][i];
        }
        pre_softmax[i] = somme;
    }
    softmax(pre_softmax, predictions, NB_neurones_C2);
}
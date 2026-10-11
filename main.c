#include <stdio.h>

#include "donnees.h"
#include "perceptron.h"

int main() {
    float longueur_sepale[150], largeur_sepale[150], longueur_petale[150], largeur_petale[150];
    int famille[150];   // Rempli par des 0, 1, 2, respectivement les famille 0, 1 et 2
    double predictions[3];  // Stocke les probabilités d'appartenance à chaque famille
    int i, j;

    double jeux_test_lineaire[NB_data][4] = {       // vecteurs de test linearisés
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

/* Jeu de coefficients pour un réseau 4 entrées, 3 neurones couche1 */
/* 3 neurones couches 2 et 3 sorties */		
/* Les elements [TAILLE_entree][] de coef_MAT1 contiennent les biais*/
/* Les elements [NB_neurones_C1][] de coef_MAT2 contiennent les biais*/
/* 15 sur 15 résultats (100%) correct avec cet ensemble de coefficients */
double coef_MAT1[TAILLE_entree+1][NB_neurones_C1] = 
			{{ +1.70, +2.58, -1.87}, 
			{+1.56, +4.04, -5.81}, 
			{-2.68, -3.84, +4.21}, 
			{-0.02, -6.49, +6.97}, 
			{-4.07, +7.31, -8.16}};
			
double coef_MAT2[NB_neurones_C1+1][NB_neurones_C2] = 
			{{ +9.00, -10.75, -1.38},
			{-1.12, +4.68, -5.82}, 
			{-3.43, -5.32, +5.60}, 
			{-3.30, +1.42, -1.22 }};

    lire_donnees(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille);
    normalise_tout(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale);
    for (i = 0; i < NB_data; i++) {
        prediction(jeux_test_lineaire[i], coef_MAT1, coef_MAT2, predictions);
        for (j = 0; j < 3; j++) {
            printf("%f | ", predictions[j]);
        }
        printf("\n");
    }

    return 0;
}
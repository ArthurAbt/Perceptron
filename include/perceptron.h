#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define NB_neurones_C1 3    
#define NB_neurones_C2 3	// Impérativement égal au nombre de sorties

#define TAILLE_entree	4   // 4 données d'entree et une valeur de sortie

#define NB_data 15          // Test avec 15 vecteurs d'entree

double act_tanh(double x);

void softmax(const double in[], double out[], int nb);

void prediction(double fleur[4], double coef_MAT1[TAILLE_entree+1][NB_neurones_C1], double coef_MAT2[NB_neurones_C1+1][NB_neurones_C2], double predictions[3]);

#endif
#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define NB_neurones_C1 3    
#define NB_neurones_C2 3	// Impérativement égal au nombre de sorties

#define TAILLE_entree	4   // 4 données d'entree et une valeur de sortie

#define NB_data 15          // Test avec 15 vecteurs d'entree

/***
 * @brief fonction d'activation arctanh, elle retourne un double (float avec beaucoup de décimal) correspondant à atanh(x)
 * @param x nombre réel duquel on souhaite calculer l'arc tangente hyerbolique
 */
double act_tanh(double x);

/***
 * @brief fonction d'activation softmax. Elle prend un tableau d'entrée, trouve sa plus haute valeur (max_softmax), parcours les entrées x et calculs exp(x - max_softmax), puis fait un dernier parcours permettant de normaliser ces valeurs et de les stocker
 * @param in tableau contenant des valeurs d'entrée sous formes de double
 * @param out tableau qui contendra softmax(in) à chaque valeur d'entrée in[i] correspond sa sortie out[i] = softmax(i)
 * @param nb taille du tableau in qui impose également len(out) = nb
 */
void softmax(const double in[], double out[], int nb);

/***
 * @brief Cette fonction retourne un tableau de 2 double : la famille de la fleur passée en entrée et la probabilité que celle-ci appartienne à cette famille.
 * @param fleur tableau contenant les 4 caractéristique (longueur/largeur du sépale et longueur/largeur du pétale) de la fleur dont on cherche la famille
 * @param coef_MAT1 matrice contenant les coefficients et biais des neurones de la première couche, les premières lignes contiennent les coefficients qui pondèrent chaque entrée tandis que la dernière contient les biais de chaque neurone (de la couche 1)
 * @param coef_MAT2 matrice contenant les coefficients et biais des neurones de la seconde couche, les premières lignes contiennent les coefficients qui pondèrent chaque sortie de C1 et entrée de C2 tandis que la dernière contient les biais de chaque neurone (de la couche 2)
 * @param proba_familles proba d'appartenance à chaque famille
 */
void prediction(double fleur[4], double coef_MAT1[TAILLE_entree+1][NB_neurones_C1], double coef_MAT2[NB_neurones_C1+1][NB_neurones_C2], double probra_familles[3]);

#endif
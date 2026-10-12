#ifndef DONNEES_H
#define DONNEES_H

/***
 * @brief Cette fonction parcours le fichier data_iris.csv et écrit ses valeurs dans les les 4 tableaux en paramètres
 * @param famille Contient la famille (0, 1, 2) de chaque iris d'entrée
 */
void lire_donnees(float longueur_sepale[150], float largeur_sepale[150], float longueur_petale[150], float largeur_petale[150], int famille[150]);

/***
 * @brief Cette fonction calcul la valeur moyenne des 150 valeurs passées en entrée
 * @param donnees tableau contenant 150 caractéristiques de fleurs (ex : longueur_sepale[150])
 */
float moyenne(float donnees[150]);

/***
 * @brief Cette fonction calcul l'écart type des 150 valeurs passées en entrée
 * @param donnees tableau contenant 150 caractéristiques de fleurs (ex : longueur_sepale[150])
 */
float ecart_type(float donnees[150]);

/***
 * @brief Cette fonction normalise les 150 valeurs passées en entrée selon la formule : v_norm = (valeur_d'entrée - moyenne) * écart_type
 * @param donnees tableau contenant 150 caractéristiques de fleurs (ex : longueur_sepale[150])
 */
void normalise(float donnees[150]);

/***
 * @brief Cette fonction normalise les valeurs de tous les tableaux passés en paramètre
 * @param longueur_sepale Tableau qui contient initialement les 150 longueurs des sépales brut et qui recevra les longueurs des 150 sépales normalisés
 * @param largeur_sepale Contiendra les largeurs des 150 sépales normalisés
 * @param longueur_petale Contiendra les longueurs des 150 pétales normalisés
 * @param largeur_petale Contient les largeurs des 150 pétales normalisés
 */
void normalise_tout(float longueur_sepale[150], float largeur_sepale[150], float longueur_petale[150], float largeur_petale[150]);

#endif
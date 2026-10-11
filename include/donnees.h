#ifndef DONNEES_H
#define DONNEES_H

void lire_donnees(float longueur_sepale[150], float largeur_sepale[150], float longueur_petale[150], float largeur_petale[150], int famille[150]);

float moyenne(float donnees[150]);

float ecart_type(float donnees[150]);

void normalise(float donnees[150]);

void normalise_tout(float longueur_sepale[150], float largeur_sepale[150], float longueur_petale[150], float largeur_petale[150]);

#endif
#ifndef ORCHESTRATEUR_H
#define ORCHESTRATEUR_H

    typedef struct {
        double e1;
        double e2;
        double e3;
        double e4;
    } ENTREES;

/***
 * @brief Cette fonction gère toute la partie communication
 * @param longueur_sepale tableau contenant la longueur des 150 sépales
 * @param largeur_sepale tableau contenant la largeur des 150 sépales
 * @param longueur_petale tableau contenant la longueur des 150 pétales
 * @param largeur_petale tableau contenant la largeur des 150 pétales
 */
void executer_systeme_ipc(double longueur_sepale[150], double largeur_sepale[150], double longueur_petale[150], double largeur_petale[150], int famille[150]);

void my_handler();

#endif
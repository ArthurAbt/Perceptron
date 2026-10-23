#ifndef MEMOIRE_H
#define MEMOIRE_H

#include <sys/types.h>  // Nécéssaire au prototype des fonctions
#include <sys/ipc.h>

typedef int SEMAPHORE;



/***
 * @brief Cette fonction crée et initialise un groupe de sémaphores
 * @param key Clé utilisée pour la création du groupe de sémaphores
 * @param nb_sem Nombre de sémaphores à crée
 * @param val_init Tableau de short contenant les valeurs initiales de chaque sémaphore du groupe
 */
SEMAPHORE Creer_Utiliser_sem(key_t key, int nb_sem, short *val_init);

/***
 * @brief Cette fonction crée une clé à partir d'un fichier
 * @param nom_fichier Chemi de fichier, il sera utiliser par ftok() afin de crée une clé à partir des données du fichier en question
 */
key_t Creer_cle(char *nom_fichier);

/***
 * @brief Cette fonction détruit le sémaphore passé en paramètre
 * @param sem Identifiant du sémaphore à détruire
 */
void Detruire_sem(SEMAPHORE sem);

/***
 * @brief Cette fonction permet de modifier la valeur d'un sémaphore
 * @param sem Identifiant du sémaphore a modifié
 * @param val Valeur (int) à additioner au sémaphore
 */
void Changer_sem(SEMAPHORE sem, int val);

/***
 * @brief Cette fonction permet d'ajouter -1 (ou de soustraire 1) au sémaphore passé en paramètre
 * @param sem Identifiant du sémaphore à modifié
 */
void P(SEMAPHORE sem);

/***
 * @brief Cette fonction permet d'ajouter 1 au sémaphore passé en paramètre
 * @param sem Identifiant du sémaphore à modifié
 */
void V(SEMAPHORE sem);

#endif
#ifndef MEMOIRE_H
#define MEMOIRE_H

#include <sys/types.h>
#include <sys/ipc.h>

typedef int SEMAPHORE;




SEMAPHORE Creer_Utiliser_sem(key_t key, int nb_sem, short *val_init);
key_t Creer_cle(char *nom_fichier);
void Detruire_sem(SEMAPHORE sem);
void Changer_sem(SEMAPHORE sem, int val);
void P(SEMAPHORE sem);
void V(SEMAPHORE sem);

#endif
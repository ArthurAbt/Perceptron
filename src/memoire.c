#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "memoire.h"


SEMAPHORE Creer_Utiliser_sem(key_t key, int nb_sem, short *val_init) {
  SEMAPHORE sem;
  sem = semget(key, nb_sem,IPC_EXCL|IPC_CREAT|0666);
  if (sem > 0) {  // Si la creation a reussi (le semaphore n'existait pas avant)
    semctl(sem,0,SETALL,val_init);
  }
  else {  // On recupère l'identifiant du semaphore si celui ci a déjà été crée
    sem = semget(key,1,0);
  }
  return sem;
}

key_t Creer_cle(char *nom_fichier) {
  key_t cle;
  if ((cle = ftok(nom_fichier,'0')) == -1) {
    perror("Creer_cle");
    exit(EXIT_FAILURE);
  }
  return cle;
}


void Detruire_sem(SEMAPHORE sem) {
  if (semctl(sem,0,IPC_RMID,0) != 0) {
    perror("Detruire_sem");
    exit(EXIT_FAILURE);
  }
}

void Changer_sem(SEMAPHORE sem, int val) {
  struct sembuf sb[1];

  sb[0].sem_num =0;
  sb[0].sem_op = val;
  sb[0].sem_flg=0;

  if (semop(sem,sb,1) != 0) {
    perror("Changer_sem");
    exit(EXIT_FAILURE);
  }
}

void P(SEMAPHORE sem) {
  Changer_sem(sem,-1);
}

void V(SEMAPHORE sem) {
  Changer_sem(sem,1);
}
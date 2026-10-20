#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sys/wait.h"

#include "orchestrateur.h"
#include "donnees.h"
#include "perceptron.h"
#include "memoire.h"

void handler_depart(){} // Cette fonction est vide est sert seulement à attendre SIGUSR1

void executer_systeme_ipc(double longueur_sepale[150], double largeur_sepale[150], double longueur_petale[150], double largeur_petale[150], int famille[150]){
    int tube_e1[2]; // Cest 4 tubes permettront de transmettre les 4 caractéristiques des différentes fleurs
	int tube_e2[2];
    int tube_e3[2];
	int tube_e4[2];

    int tube_s1[2]; // Ces 3 tubes permettront de transmettre les 3 sorties du réseau de neurone
	int tube_s2[2];
    int tube_s3[2];

    int tube_satt[2];   // Ce tube permet de transmettre la sortie attendue (satt) à l'analyseur
    int tube_err[2];    //Ce tube permet de transmettre l'erreur liée aux choix des coeffs et biais lors de la mise en place du réseau de neurones

    double fleur[4];
    double proba_familles[3];
    double sorties[3];
    
    
    int shmid;
    SEMAPHORE sem;
    key_t cle1;
    short val_init[1]={0};

    int i, j;
    
    
    double erreur = 0, erreur_p;
    
    pid_t pid_couche1, pid_couche2, pid_lecteur, pid_analyseur;


    typedef struct {
        double e1;
        double e2;
        double e3;
        double e4;
    } ENTREES;


    ENTREES *ptr;


    if (pipe(tube_e1) == -1 || pipe(tube_e2) == -1 || pipe(tube_e3)== -1 || pipe(tube_e4)== -1 || pipe(tube_s1)== -1 || pipe(tube_s2)== -1 || pipe(tube_s3) == -1 || pipe(tube_satt) == -1 || pipe(tube_err) == -1) {  // Gestion erreur des pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid_lecteur = fork()) == 0) {  // On est un fils et on effectue la partie Lecteur

        signal(SIGUSR1, handler_depart);    // On déroute le signal SIGUSR1 vers handler_depart. Dès que SIGUSR1 est reçu, on effectue la fonction handler_depart
        pause();    // On se bloque jusqu'à réception du signal SIGUSR1

        lire_donnees(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille); // Permet d'extraire toute les données du tableau datairis.csv et de les stocker dans les differnetes listes
        normalise_tout(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale); // Normalise toute nos valeurs (qui le sont deja pour celles de test)

        close(tube_e1[0]);  // On ferme les tubes (lecture) pour pouvoir écrire
        close(tube_e2[0]);
        close(tube_e3[0]);
        close(tube_e4[0]);
        close(tube_satt[0]);

        for (i = 0; i < 150; i++) {
            write(tube_e1[1], &longueur_sepale[i], sizeof(double));
            write(tube_e2[1], &largeur_sepale[i], sizeof(double));
            write(tube_e3[1], &longueur_petale[i], sizeof(double));
            write(tube_e4[1], &largeur_petale[i], sizeof(double));

            write(tube_satt[1], &famille[i], sizeof(int));
        }

        exit(0);
    }


    shmid = shmget(IPC_PRIVATE, sizeof(ENTREES), IPC_CREAT|0666);
    if (shmid == -1) {
    perror("shmget");
    exit(EXIT_FAILURE);
     }


     cle1 = Creer_cle("src/orchestrateur.c");
     sem=Creer_Utiliser_sem(cle1,1,val_init);


    if ((pid_couche1 = fork()) == 0){


        ptr = (ENTREES *) shmat(shmid, 0, 0);
        if ( ptr == (ENTREES *)-1 ) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        close(tube_e1[1]);  // On ferme les tubes (lecture) pour pouvoir écrire
        close(tube_e2[1]);
        close(tube_e3[1]);
        close(tube_e4[1]);

        for (i = 0; i < 150; i++) {
            read(tube_e1[0], &(ptr->e1), sizeof(double));
            read(tube_e2[0], &(ptr->e2), sizeof(double));
            read(tube_e3[0], &(ptr->e3), sizeof(double));
            read(tube_e4[0], &(ptr->e4), sizeof(double));

            V(sem);
            P(sem);

        }


        /* Detachement de la memoire partagee */
        shmdt(ptr);
        
        /* Destruction du segment de memoire partagee */
        shmctl(shmid, IPC_RMID, NULL);


        exit(0);


    }

    if ((pid_couche2 = fork()) == 0){ // On est un fils et on effectue la partie couche 2

            

            ptr = (ENTREES *) shmat(shmid, 0, 0);
            if ( ptr == (ENTREES *)-1 ) {
                perror("shmat");
                exit(EXIT_FAILURE);
            }

            


            close(tube_s1[0]);  // On ferme les tubes (lecture) pour pouvoir écrire
            close(tube_s2[0]);
            close(tube_s3[0]);

            for (i = 0; i < 150; i++) {

                P(sem); // Attends que couche 1 est fini.
                fleur[0] = ptr->e1;
                fleur[1] = ptr->e2;
                fleur[2] = ptr->e3;
                fleur[3] = ptr->e4;

                

                validation_1_donnee(fleur, proba_familles); // Coeur du programme, c'est le réseau de neurones

                write(tube_s1[1], &proba_familles[0], sizeof(double));
                write(tube_s2[1], &proba_familles[1], sizeof(double));
                write(tube_s3[1], &proba_familles[2], sizeof(double));

                V(sem);
            }


            /* Destruction du semaphore */
            Detruire_sem(sem);

            /* Detachement de la memoire partagee */
            shmdt(ptr);
            
            /* Destruction du segment de memoire partagee */
            shmctl(shmid, IPC_RMID, NULL);

            exit(0);
    }

    if ((pid_analyseur = fork()) == 0) {  // On est un fils et on effectue la partie Analyseur

        close(tube_s1[1]);
        close(tube_s2[1]);
        close(tube_s3[1]);

        close(tube_satt[1]);
        close(tube_err[0]);

        for (i = 0; i < 150; i++) {
            double proba_max = 0;
            int f, satt;

            read(tube_s1[0], &sorties[0], sizeof(double));
            read(tube_s2[0], &sorties[1], sizeof(double));
            read(tube_s3[0], &sorties[2], sizeof(double));

            read(tube_satt[0], &satt, sizeof(int));

            for (j = 0; j < 3 ; j++){
                if (sorties[j] > proba_max){
                    proba_max = sorties[j];
                    f = j;
                }
            }

            if (f != satt){
                erreur += 1;
            }
        }
        erreur = (erreur / 150) * 100;
        write(tube_err[1], &erreur, sizeof(double));

        exit(0);
    }

    else {  // On est le père et on effectue la partie Moniteur
        close(tube_e1[0]);  // On ferme les tubes
        close(tube_e2[0]);
        close(tube_e3[0]);
        close(tube_e4[0]);
        close(tube_e1[1]);
        close(tube_e2[1]);
        close(tube_e3[1]);
        close(tube_e4[1]);
        close(tube_s1[0]);
        close(tube_s2[0]);
        close(tube_s3[0]);
        close(tube_s1[1]);
        close(tube_s2[1]);
        close(tube_s3[1]);
        close(tube_satt[0]);
        close(tube_satt[1]);
        close(tube_err[1]); // On garde uniquement garder ouvert tube_err[0] car on va chercher à lire l'erreur de calcul dedans

        sleep(1);   // On ajoute un temps d'attente afin d'être sûr que tous les fils aient le temps d'être crée AVANT l'envoi de SIGUSR1
        kill(pid_lecteur, SIGUSR1); // Envoie du signal de départ

        read(tube_err[0], &erreur_p, sizeof(double));
        printf("L'erreur de classification est de %.2f%% !\n", erreur_p);

        for (i = 0; i < 3; i++) {
            wait(NULL); // On attend la mort des 3 fils (lecteur, application, analyseur)
        }
    }
}
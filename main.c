#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "donnees.h"
#include "perceptron.h"

void Moniteur(double longueur_sepale[150], double largeur_sepale[150], double longueur_petale[150], double largeur_petale[150], int famille[150]){
    int tube_e1[2];
	int tube_e2[2];
    int tube_e3[2];
	int tube_e4[2];

    int tube_s1[2];
	int tube_s2[2];
    int tube_s3[2];

    double fleur[4];
    double proba_familles[3];
    double sorties[3];
    int i, j;
    double erreur = 0;
    

    pid_t fils;

    if (pipe(tube_e1) == -1 || pipe(tube_e2) == -1 || pipe(tube_e3)== -1 || pipe(tube_e4)== -1 || pipe(tube_s1)== -1 || pipe (tube_s2)== -1 || pipe (tube_s3) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }


    if ((fils = fork()) != 0){ // Pere qui fait la partie du Moniteur
        lire_donnees(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille); // Permet d'extraire toute les données du tableau datairis.csv et de les stocker dans les differnetes listes
        normalise_tout(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale); // Normalise toute nos valeurs (qui le sont deja pour celles de test)

        close(tube_e1[0]);
        close(tube_e2[0]);
        close(tube_e3[0]);
        close(tube_e4[0]);

        for (i = 0; i < 150; i++) {
            double proba_max = 0;
            int f;

            write(tube_e1[1],&longueur_sepale[i],sizeof(double));
            write(tube_e2[1],&largeur_sepale[i],sizeof(double));
            write(tube_e3[1],&longueur_petale[i],sizeof(double));
            write(tube_e4[1],&largeur_petale[i],sizeof(double));

            read(tube_s1[0],&sorties[0],sizeof(double));
            read(tube_s2[0],&sorties[1],sizeof(double));
            read(tube_s3[0],&sorties[2],sizeof(double));

            for (j = 0; j < 3 ; j++){
                if (sorties[j] > proba_max){
                    proba_max = sorties[j];
                    f = j;
                }
            }

            if (f != famille[i]){
                erreur += 1;
            }
        }
        printf("L'erreur de classification est de %.2f %% soit %d erreurs !\n", (erreur / 150) * 100, (int) erreur);

        close(tube_e1[1]);
        close(tube_e2[1]);
        close(tube_e3[1]);
        close(tube_e4[1]);
        close(tube_s1[0]);
        close(tube_s2[0]);
        close(tube_s3[0]);
        
        wait(NULL);
    }
    else {
        for (i = 0; i < 150; i++) {
            read(tube_e1[0],&fleur[0],sizeof(double));
            read(tube_e2[0],&fleur[1],sizeof(double));
            read(tube_e3[0],&fleur[2],sizeof(double));
            read(tube_e4[0],&fleur[3],sizeof(double));

            validation_1_donnee(fleur, proba_familles);

            write(tube_s1[1],&proba_familles[0],sizeof(double));
            write(tube_s2[1],&proba_familles[1],sizeof(double));
            write(tube_s3[1],&proba_familles[2],sizeof(double));
        }

        close(tube_e1[0]);
        close(tube_e2[0]);
        close(tube_e3[0]);
        close(tube_e4[0]);
        close(tube_s1[1]);
        close(tube_s2[1]);
        close(tube_s3[1]);

        exit(0);
    }
}

int main() {
    double longueur_sepale[150], largeur_sepale[150], longueur_petale[150], largeur_petale[150]; // Les données d'entrées
    int famille[150];   // Rempli par des 0, 1, 2, respectivement les famille 0, 1 et 2 (50 premiers sont de la famille 0,les 50 suivant de la famille 1 et les 50 derniers de a famille)
    
    Moniteur(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille);

return 0;
}
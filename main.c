#include <stdio.h>

#include "donnees.h"
#include "perceptron.h"

void Application ();
void Moniteur (double longueur_sepale[], double largeur_sepale[],double longueur_petale[], double largeur_petale[]);
int main() {
    float longueur_sepale[150], largeur_sepale[150], longueur_petale[150], largeur_petale[150]; // Les données d'entrées
    int famille[150];   // Rempli par des 0, 1, 2, respectivement les famille 0, 1 et 2 (50 premiers sont de la famille 0,les 50 suivant de la famille 1 et les 50 derniers de a famille)

    





    //validation_jeux_donnees(15, jeux_test_lineaire, famille);

return 0;
}

void Moniteur(double longueur_sepale[150], double largeur_sepale[150], double longueur_petale[150], double largeur_petale[150];){
    int tube_e1[2];
	int tube_e2[2];
    int tube_e3[2];
	int tube_e4[2];
    int tube_s1[2];
	int tube_s2[2];
    int tube_s3[2];
    double fleur[4];
    double resultats[3];
    double sorties[3];
    double proba_max=0;
    int f;
    double erreur=0;
    

    pid_t fils;

    if (pipe(tube_e1) == -1 || pipe(tube_e2) == -1 || pipe(tube_e3)== -1 || pipe(tube_e4)== -1 || pipe(tube_s1)== -1 || pipe (tube_s2)== -1 || pipe (tube_s3) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }


    if ( (fils=fork()) =! 0){ // Pere qui fait la partie du Moniteur
        lire_donnees(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale, famille); // Permet d'extraire toute les données du tableau datairis.csv et de les stocker dans les differnetes listes
        normalise_tout(longueur_sepale, largeur_sepale, longueur_petale, largeur_petale); // Normalise toute nos valeurs (qui le sont deja pour celles de test)
        write(tube_e1[1],longueur_sepale[0],sizeof(double));
        write(tube_e2[1],largeur_sepale[0],sizeof(double));
        write(tube_e3[1],longueur_petale[0],sizeof(double));
        write(tube_e4[1],largeur_petale[0],sizeof(double));

        close(tube_e1[0]);
        close(tube_e1[1]);
        close(tube_e2[0]);
        close(tube_e2[1]);
        close(tube_e3[0]);
        close(tube_e3[1]);
        close(tube_e4[0]);
        close(tube_e4[1]);


        read(tube_s1[1],sorties[0],sizeof(double));
        read(tube_s2[1],sorties[1],sizeof(double));
        read(tube_s3[1],sorties[2],sizeof(double));

        for (int i = 0; i<3 ; i++){
            if (sorties[i]>proba_max){
                proba_max=sorties[i];
                f=i;
            }
        }
        
        if (f!= famille[0]){
            erreur+=1;
        }
        else {
            printf("oui");
        }
    }

    else {
        read(tube_e1[0],fleur[0],sizeof(double));
        read(tube_e2[0],fleur[1],sizeof(double));
        read(tube_e3[0],fleur[2],sizeof(double));
        read(tube_e4[0],fleur[3],sizeof(double));

        valdation_1_donnee(fleur,resultats)

        write(tube_s1[1],resultats[0],sizeof(double));
        write(tube_s2[1],resultats[1],sizeof(double));
        write(tube_s3[1],resultats[2],sizeof(double));
    }
    



}



# Mini-projet Perceptron - Unix IESE4 - MATEUS Exaucé & ABT Arthur

## Description du Projet
Ce projet en langage C implémente un modèle mathématique de perceptron (réseau de neurones) destiné à résoudre un problème classique de classification : la reconnaissance d'espèces de fleurs d'Iris (Setosa, Versicolor, et Virginica) à partir de leurs caractéristiques physiques (Longueurs et largeurs des sépales et pétales). Ce développement s'inscrit dans le cadre du module Unix IESE4 de Polytech Grenoble, avec pour objectif pédagogique principal la mise en pratique des communications inter-processus (IPC) sous Unix.

Le réseau de neurones est un perceptron multicouche structuré de la manière suivante :
* **4 entrées** correspondant aux caractéristiques normalisées de la fleur (longueur/largeur du sépale, longueur/largeur du pétale).
* **2 couches** composées de 3 neurones chacune.
* **3 sorties** calculant les probabilités d'appartenance à chaque famille de fleur.
* **Fonctions d'activation** : `tanh` pour la couche d'entrée, `softmax` pour la couche de sortie.

L'apprentissage ayant déjà été réalisé, les coefficients et biais du modèle sont fournis de base dans le code.

## Architecture Multiprocessus
Afin d'exploiter les systèmes Unix, l'application est décomposée en 4 processus distincts communiquant par des tubes (`pipes`) et se synchronise à l'aide de signaux.

* **Le Moniteur (Processus Père) :** Orchestre la mise en place du système. Il génère l'ensemble des tubes, crée les processus fils via la primitive `fork()`, envoie le signal de départ, et affiche finalement les statistiques d'erreur globales.
* **Le Lecteur :** À la réception du signal `SIGUSR1` émis par le Moniteur, ce processus lit les données du fichier `data_iris.csv`, normalise les valeurs brutes à l'aide de la moyenne et de l'écart-type, puis transmet ces données via 4 tubes distincts vers l'Application. Il transmet également la famille attendue à l'Analyseur.
* **L'Application :** Le cœur du calcul. Il lit en boucle les caractéristiques des fleurs depuis les tubes d'entrée, applique les calculs matriciels du perceptron, et écrit ses probabilités de prédiction dans 3 tubes de sortie.
* **L'Analyseur :** Récupère les prédictions de l'Application et la famille attendue envoyée par le Lecteur. Il compare ces données à chaque itération pour déterminer le taux d'erreur de classification de l'algorithme.

## Synchronisation et Communication (IPC)
Le projet met en œuvre de manière stricte les primitives POSIX suivantes :
* **Pipes :** Utilisation de nombreux descripteurs de fichiers pour la transmission fluide des vecteurs de données (`double`) et de la vraie famille (`int`). Chaque processus gère la fermeture des descripteurs inutilisés pour éviter tout blocage.
* **Signaux :** Déroutement du signal `SIGUSR1` avec la primitive `signal()` couplé à une mise en attente via `pause()` pour synchroniser le démarrage de la lecture.
* **Contrôle d'exécution :** Utilisation de `kill()` pour l'envoi de signaux et de `wait()` pour l'attente de la terminaison propre des processus enfants.

## Structure de l'Arborescence
* `include/` : Contient les fichiers d'en-tête (headers `.h`).
  * `donnees.h` : Prototypes des fonctions de parsing et de normalisation.
  * `perceptron.h` : Prototypes liés aux mathématiques du réseau de neurones.
  * `orchestrateur.h` : Prototype du système de gestion des processus IPC.
* `src/` : Contient le code source (fichiers `.c`).
  * `donnees.c` : Traitement, lecture du fichier CSV et normalisation.
  * `perceptron.c` : Calculs des poids, biais et fonctions d'activation.
  * `orchestrateur.c` : Déploiement des `fork()`, routage des `pipes` et gestion des signaux.
* `main.c` : Point d'entrée allégé appelant l'orchestrateur.
* `Makefile` : Fichier de compilation modulaire.
* `data_iris.csv` : La base de données comportant 150 spécimens de fleurs.

## Compilation et Exécution
Ce projet utilise un `Makefile` standard pour faciliter sa construction.

1. Placez-vous à la racine du projet dans le terminal.
2. Compilez le projet à l'aide de la commande :
    'make'
   make
3. Exécutez le code à l'aide de la commande suivante :
    '/bin/code'
# Choix du compilateur
CC = gcc

# Options de compilation (-Iinclude dit à gcc de chercher les .h dans le dossier include)
CFLAGS = -Wall -Wextra -Iinclude

# Nom de l'exécutable final demandé
TARGET = code

# Liste des fichiers objets
OBJ = main.o donnees.o perceptron.o

# Règle principale (celle exécutée quand on tape "make")
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm

# Règles pour créer chaque fichier objet à partir des bons dossiers
main.o: main.c include/donnees.h include/perceptron.h
	$(CC) $(CFLAGS) -c main.c

donnees.o: src/donnees.c include/donnees.h
	$(CC) $(CFLAGS) -c src/donnees.c -o donnees.o

perceptron.o: src/perceptron.c include/perceptron.h
	$(CC) $(CFLAGS) -c src/perceptron.c -o perceptron.o

# Règle pour tout nettoyer (taper "make clean")
clean:
	rm -f *.o $(TARGET)
# Choix du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Iinclude

# Nom de l'exécutable final (placé dans le dossier bin/)
TARGET = bin/code

# Liste des fichiers objets
OBJ = obj/main.o obj/donnees.o obj/perceptron.o obj/orchestrateur.o obj/memoire.o

# Règle principale
$(TARGET): $(OBJ) | bin
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm

# Règle pour s'assurer que le dossier bin existe
bin:
	mkdir -p bin

# Règle pour s'assurer que le dossier obj existe
obj:
	mkdir -p obj

# Règles pour créer chaque fichier objet (on ajoute "| obj" comme dépendance pour garantir sa création)
obj/main.o: src/main.c include/donnees.h include/perceptron.h include/orchestrateur.h include/memoire.h | obj
	$(CC) $(CFLAGS) -c main.c -o obj/main.o

obj/donnees.o: src/donnees.c include/donnees.h | obj
	$(CC) $(CFLAGS) -c src/donnees.c -o obj/donnees.o

obj/perceptron.o: src/perceptron.c include/perceptron.h | obj
	$(CC) $(CFLAGS) -c src/perceptron.c -o obj/perceptron.o

obj/orchestrateur.o: src/orchestrateur.c include/orchestrateur.h | obj
	$(CC) $(CFLAGS) -c src/orchestrateur.c -o obj/orchestrateur.o

obj/memoire.o: src/memoire.c include/memoire.h | obj
	$(CC) $(CFLAGS) -c src/memoire.c -o obj/memoire.o

# Règle pour tout nettoyer (supprime le contenu des dossiers obj et bin)
clean:
	rm -f obj/*.o $(TARGET)
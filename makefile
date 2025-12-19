# Nom de l'exécutable C
EXEC = wildwater

# Compilateur et options : -g pour le debug, -O0 pour pas d'optimisation
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0

# Fichiers sources C à compiler
SRCS = main.c avl.c histogramme.c fuites.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Cible par défaut : Compiler le projet
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJS)
	@echo "Liaison de l'exécutable..."
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Règle de compilation des fichiers objets
%.o: %.c
	@echo "Compilation de $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Cible 'clean' : Supprimer les fichiers générés
clean:
	@echo "Nettoyage du projet..."
	rm -f $(OBJS) $(EXEC)
	# Supprimer les fichiers de sortie demandés par le projet
	rm -f vol_max.dat vol_src.dat vol_real.dat leaks.dat
	rm -f *.png
	@echo "Nettoyage terminé."

.PHONY: all clean

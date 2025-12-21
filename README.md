# C-WildWater : Analyse de Réseau de Distribution d'Eau

## Description du Projet

Ce projet analyse un réseau de distribution d'eau à partir d'une base de données volumineuse. Il permet de visualiser les capacités des usines (via des histogrammes) et de détecter les pertes d'eau (fuites).
L'architecture technique repose sur :
* Un **Script Shell** (`myScript.sh`) pour l'organisation et l'interface utilisateur.
* Un **Programme C** (`main.c`, `avl.c`, `fuites.c`, `histogramme.c`) utilisant des **AVL** et des **Graphes** pour la performance.
* **Gnuplot** pour la génération automatique des graphiques.

## Installation et Compilation

### Prérequis
* Environnement Linux/Unix.
* `gcc` (Compilateur C).
* `make` (Utilitaire de compilation).
* `gnuplot` (Pour générer les images des histogrammes).

### Compilation
Le projet utilise un fichier `makefile`.

1. **Compiler le projet :**
    ```bash
    make
    ```
    *(Cela générera l'exécutable nécessaire au fonctionnement du script)*

2. **Nettoyer les fichiers temporaires :**
    ```bash
    make clean
    ```

## Utilisation

L'unique point d'entrée est le script **`myScript.sh`**. Il faut lui fournir le fichier de données (présent dans le dossier : `c-wildwater_v0.dat`).

### Génération d'Histogrammes (`histo`)
Analyse les volumes des usines et génère un graphique `.png`.

* **`max`** : Capacité maximale de traitement.
* **`src`** : Volume total capté par les sources.
* **`real`** : Volume réellement traité (après pertes de captage).

**Droits d'exécution du Script Shell :**
Avant de lancer le programme, vous devez autoriser l'exécution du script principal, ensuite il y a l'installation de gnuplot et les commandes à exécuter :
```bash
chmod +x myScript.sh
sudo apt-get update && sudo apt-get install -y gnuplot
./myScript.sh c-wildwater_v0.dat leaks "nom de l'usine" 
./myScript.sh c-wildwater_v0.dat histo max
./myScript.sh c-wildwater_v0.dat histo src
./myScript.sh c-wildwater_v0.dat histo real

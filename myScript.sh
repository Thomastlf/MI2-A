#!/bin/bash

function exit_script{
    END_TIME=$(date +%s%3N)
    DURATION=$((END_TIME - START_TIME))
    echo "Durée totale du script: $DURATION ms"
    exit $1
}

START_TIME=$(date +%s%3N)

if [ "$#" -ne 3 ]; then #on vérifie que le script a bien pris 3 arguments
	echo "Erreur. Il faut exactement trois arguments."
	exit_script 1
fi

executable="./wildwater"
fichier="$1"
commande="$2"
parametre="$3"

if [ ! -x "$executable" ]; then #on vérifie que l'exécutable existe, sinon on essaye de le créer
  echo "L'exécutable C n'existe pas ou n'est pas exécutable. Tentative de compilation avec make..."
  make
  if [ $? -ne 0 ]; then
    echo "Erreur de compilation du programme C."
    exit_script 2
  fi
fi

if [ ! -f "$fichier" ]; then #on vérifie que le premier argument est bien un fichier
  echo "Erreur. Le premier argument doit être un fichier."
  exit_script 3
fi

if [ "$commande" != "histo" ] && [ "$commande" != "leaks" ]; then #on vérifie que le deuxième argument est bien histo ou leaks
  echo "Erreur. Le deuxième argument doit être histo ou leaks."
  exit_script 4
fi

if [ "$commande" == "histo" ]; then #si la commande est un histo..
  if [ "$parametre" != "max" ] && [ "$parametre" != "src" ] && [ "$parametre" != "real" ]; then
    echo "Erreur. Dans le cas de l'histogramme le deuxième argument doit être max, src ou real."
    exit_script 5
  fi


  
else #si la commande est un leaks..
  if [

exit_script 0

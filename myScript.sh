#!/bin/bash

function exit_script {
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
  	fichier_sortie="vol_${parametre}.dat"
	echo "Calcul de l'histogramme et création de $fichier_sortie en cours..."
	"$executable" "$fichier" "$commande" "$parametre"
	if [ $? -ne 0 ];then
		echo "Erreur lors de l'exécution du programme C."
		exit_script 6
	fi

	#GNUPLOT
	
    FILE_TO_PLOT="$fichier_sortie"
    GNUPLOT_SCRIPT="plot_temp.gp"
    echo "Génération des graphiques (Tri par volume activé)..."
	cat << EOF > "$GNUPLOT_SCRIPT"
	# Configuration commune
	set terminal png size 800, 600
	set datafile separator ';'
	set style fill solid 0.8 border -1
	set grid y
	set key off
	set ylabel "Volume (M.m³)"
	set xtics rotate by -45 scale 0 font ",8"
	set boxwidth 0.8 relative
	# --- IMAGE 1 : TOP 10 (Plus grandes usines) ---
	set output 'top10_${parametre}.png'
	set title "10 Plus Grandes Usines ($parametre)"
	# TRI : On trie numériquement (n) et inversé (r) sur la col 2 pour avoir les plus gros en premier
	plot '< tail -n +2 "${FILE_TO_PLOT}" | sort -t";" -k2,2nr | head -n 10' using 0:2:xtic(1) with boxes lc rgb "#1A4974"
	# --- IMAGE 2 : BOTTOM 50 (Plus petites usines) ---
	set output 'bottom50_${parametre}.png'
	set title "50 Plus Petites Usines ($parametre)"
	# TRI : On trie numériquement (n) sur la col 2 pour avoir les plus petits en premier
	plot '< tail -n +2 "${FILE_TO_PLOT}" | sort -t";" -k2,2n | head -n 50' using 0:2:xtic(1) with boxes lc rgb "#6A8B9E"
EOF
    # Exécution de Gnuplot
    gnuplot "$GNUPLOT_SCRIPT"
    # Nettoyage
    rm "$GNUPLOT_SCRIPT"
    if [ -f "top10_${parametre}.png" ] && [ -f "bottom50_${parametre}.png" ]; then
        echo "✅ Succès : Images triées 'wildwater_top10.png' et 'wildwater_bottom50.png' générées."
    else
        echo "❌ Erreur : Une ou plusieurs images n'ont pas été créées."
    fi
    echo "Traitement histogramme '$parametre' terminé."
  
else #si la commande est un leaks..
	echo "Calcul des fuites pour l'usine '$parametre'..."
  	fuite=$("$executable" "$fichier" "$commande" "$parametre")
	if [ $? -ne 0 ]; then
		echo "Erreur lors de l'exécution du programme C."
		exit_script 7
	fi
	fichier_sortie="leaks.dat"
	if [ ! -f "$fichier_sortie" ]; then
    	echo "identifier;Leak volume (M.m³.year⁻¹)" > "$fichier_sortie"
    fi
	echo "$parametre;$fuite" >> "$fichier_sortie"
  	echo "Résultat du calcul: $fuite M.m³"
fi

exit_script 0

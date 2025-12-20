# 1. Configuration de la sortie (Format PNG)
set terminal pngcairo enhanced font 'Arial,10' size 1200, 400
set output 'wildwater_visualisation.png'

# 2. Configuration du multiplot
set multiplot layout 1, 2 title "WildWater - Analyse des Capacités Max"
set style fill solid 0.8 border -1
set grid x
set key off
set xlabel "Volume Max (M.m³)"
set ylabel ""
# Inverse l'axe Y pour que le tri soit lisible du haut vers le bas
set yrange reverse 
set boxwidth 0.9 relative

# PLOT 1: 50 Plus Petites Usines
set title "50 Plus Petites Usines"
set origin 0.0, 0.0
set size 0.5, 1.0

# Commande : lit les 50 dernières lignes (plus petites), les inverse pour l'affichage, et les trace.
# using 2:($0):ytic(1) permet de tracer un graphique à barres horizontal.
plot '< tail -n 50 vol_max.dat | tac' using 2:($0):ytic(1) with boxes lc rgb "#6A8B9E"

# PLOT 2: 10 Plus Grandes Usines
set title "10 Plus Grandes Usines"
set origin 0.5, 0.0
set size 0.5, 1.0

# Commande : lit les 10 premières lignes (plus grandes), les inverse pour l'affichage, et les trace.
plot '< head -n 10 vol_max.dat | tac' using 2:($0):ytic(1) with boxes lc rgb "#1A4974"

unset multiplot

#!/usr/bin/env bash
set terminal post enhanced colour solid font 14  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set terminal jpeg

set xlabel "Krok czasowy" # etykieta osi OX
set ylabel "Wartosc" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej


set style line 1  lc rgb 'red' lt 1 lw 2 # --- blue
set style line 2  lc rgb 'blue' lt 1 lw 2 #      .
set style line 3  lc rgb 'black' lt 1 lw 2 #      .
set style line 4  lc rgb 'green' lt 1 lw 2 #      .
set style line 5  lc rgb 'yellow' lt 1 lw 2 #      .
set style line 6  lc rgb 'violet' lt 1 lw 2 #      .
set style line 7  lc rgb 'orange' lt 1 lw 2 #      .
set style line 8  lc rgb 'pink' lt 1 lw 2 #      .
set style line 9 lc rgb 'grey' lt 1 lw 2 #      .



################################################### DRAW ####################################################

#############################################################################################################

set xlabel "nr iteracji"
set ylabel "S"
set logscale x
set title "Relaksacja wielosiatkowa_S" # tytul wykresu
set output "Relaksacja_wielosiatkowa_S.jpg" # nazwa pliku wynikowego

plot 'iteracje_k=16.dat' using 1:2 with lines title "k=16" ls 1, 'iteracje_k=8.dat' using 1:2 with lines ls 2 title "k=8", 'iteracje_k=4.dat' using 1:2 with lines ls 3 title "k=4", 'iteracje_k=2.dat' using 1:2 with lines ls 4 title "k=2", 'iteracje_k=1.dat' using 1:2 with lines ls 5 title "k=1"
#############################################################################################################

unset logscale x

#############################################################################################################



#############################################################################################################
set view map
unset contour

set out "v_k=16.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'potencjal_k=16.dat' u 1:2:3 w pm3d
#############################################################################################################
set view map
unset contour

set out "v_k=8.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'potencjal_k=8.dat' u 1:2:3 w pm3d
#############################################################################################################
set view map
unset contour

set out "v_k=4.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'potencjal_k=4.dat' u 1:2:3 w pm3d
#############################################################################################################
set view map
unset contour

set out "v_k=2.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'potencjal_k=2.dat' u 1:2:3 w pm3d
#############################################################################################################
set view map
unset contour

set out "v_k=1.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'potencjal_k=1.dat' u 1:2:3 w pm3d
#############################################################################################################


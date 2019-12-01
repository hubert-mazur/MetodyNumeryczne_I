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
set title "Relaksacja globalna_S" # tytul wykresu
set output "Relaksacja_globalna_S.jpg" # nazwa pliku wynikowego

plot 'relaksacja_globalna_S_omega=0.600000.dat' using 1:2 with lines title "w=0.6" ls 1, 'relaksacja_globalna_S_omega=1.000000.dat' using 1:2 with lines ls 2 title "w=1.0"
#############################################################################################################

set xlabel "nr iteracji"
set ylabel "S"
set logscale x
set title "Relaksacja lokalna_S" # tytul wykresu
set output "Relaksacja_lokalna_S.jpg" # nazwa pliku wynikowego

plot 'relaksacja_lokalna_S_omega=1.000000.dat' using 1:2 with lines title "w=1.0" ls 1, 'relaksacja_lokalna_S_omega=1.400000.dat' using 1:2 with lines ls 2 title "w=1.4", 'relaksacja_lokalna_S_omega=1.800000.dat' using 1:2 with lines ls 3 title "w=1.8", 'relaksacja_lokalna_S_omega=1.900000.dat' using 1:2 with lines ls 4 title "w=1.9"
#############################################################################################################

unset logscale x

#############################################################################################################



#############################################################################################################
set view map
unset contour

set out "v_omega=0.6.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'relaksacja_globalna_omega=0.600000.dat' u 1:2:3 w pm3d
#############################################################################################################
set view map
unset contour

set out "v_omega=1.0.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'relaksacja_globalna_omega=1.000000.dat' u 1:2:3 w pm3d
#############################################################################################################
set view map
unset contour

set out "v_omega=0.6_err.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'relaksacja_globalna_err_omega=0.600000.dat' u 1:2:3 w pm3d
#############################################################################################################
set view map
unset contour

set out "v_omega=1.0_err.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'relaksacja_globalna_err_omega=1.000000.dat' u 1:2:3 w pm3d

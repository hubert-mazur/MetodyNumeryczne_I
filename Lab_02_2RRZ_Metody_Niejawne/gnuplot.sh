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
set title "Metoda Picarda" # tytul wykresu
set output "MetodaPicarda.jpg" # nazwa pliku wynikowego

plot 'MetodaPicarda.dat' using 1:2 with lines title "u(t)" ls 1, 'MetodaPicarda.dat' using 1:3 with lines ls 2 title "z(t) = N - u(t)"
#############################################################################################################
set title "Metoda Newtona" # tytul wykresu
set output "MetodaNewtona.jpg" # nazwa pliku wynikowego

plot 'MetodaNewtona.dat' using 1:2 with lines title "u(t)" ls 1, 'MetodaNewtona.dat' using 1:3 with lines ls 2 title "z(t) = N - u(t)"
#############################################################################################################
set title "Metoda RK2 Niejawna" # tytul wykresu
set output "MetodaRK2Niejawna.jpg" # nazwa pliku wynikowego

plot 'Metoda_RK2.dat' using 1:2 with lines title "u(t)" ls 1, 'Metoda_RK2.dat' using 1:3 with lines ls 2 title "z(t) = N - u(t)"
################
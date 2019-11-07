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
set title "Metoda Trapezów x(t)" # tytul wykresu
set output "Metoda_Trapezów_x(t).jpg" # nazwa pliku wynikowego

plot 'MetodaTrapezow0.010000.dat' using 1:3 with lines title "TOL = 10^-2" ls 1, 'MetodaTrapezow0.000010.dat' using 1:3 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################
set title "Metoda Trapezów v(t)" # tytul wykresu
set output "Metoda_Trapezów_v(t).jpg" # nazwa pliku wynikowego

plot 'MetodaTrapezow0.010000.dat' using 1:4 with lines title "TOL = 10^-2" ls 1, 'MetodaTrapezow0.000010.dat' using 1:4 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################
set title "Metoda Trapezów dT(t)" # tytul wykresu
set output "Metoda_Trapezów_dT(t).jpg" # nazwa pliku wynikowego

plot 'MetodaTrapezow0.010000.dat' using 1:2 with lines title "TOL = 10^-2" ls 1, 'MetodaTrapezow0.000010.dat' using 1:2 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################
set title "Metoda Trapezów v(x)" # tytul wykresu
set output "Metoda_Trapezów_v(x).jpg" # nazwa pliku wynikowego

plot 'MetodaTrapezow0.010000.dat' using 3:4 with lines title "TOL = 10^-2" ls 1, 'MetodaTrapezow0.000010.dat' using 3:4 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################
#############################################################################################################
set title "Metoda RK2 x(t)" # tytul wykresu
set output "Metoda_RK2_x(t).jpg" # nazwa pliku wynikowego

plot 'MetodaRK20.010000.dat' using 1:3 with lines title "TOL = 10^-2" ls 1, 'MetodaRK20.000010.dat' using 1:3 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################
set title "Metoda RK2 v(t)" # tytul wykresu
set output "Metoda_RK2_v(t).jpg" # nazwa pliku wynikowego

plot 'MetodaRK20.010000.dat' using 1:4 with lines title "TOL = 10^-2" ls 1, 'MetodaRK20.000010.dat' using 1:4 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################
set title "Metoda RK2 dT(t)" # tytul wykresu
set output "Metoda_RK2_dT(t).jpg" # nazwa pliku wynikowego

plot 'MetodaRK20.010000.dat' using 1:2 with lines title "TOL = 10^-2" ls 1, 'MetodaRK20.000010.dat' using 1:2 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################
set title "Metoda RK2 v(x)" # tytul wykresu
set output "Metoda_RK2_v(x).jpg" # nazwa pliku wynikowego

plot 'MetodaRK20.010000.dat' using 3:4 with lines title "TOL = 10^-2" ls 1, 'MetodaRK20.000010.dat' using 3:4 with lines ls 2 title "TOL = 10^-5"
#############################################################################################################


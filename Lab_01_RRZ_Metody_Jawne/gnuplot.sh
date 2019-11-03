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
set title "Metoda Jawna Eulera" # tytul wykresu
set output "MetodaJawnaEulera.jpg" # nazwa pliku wynikowego

plot 'metodaJawnaEulera__T=0.010000.dat' using 1:2 with lines title "Krok = 0.01" ls 1, 'metodaJawnaEulera__T=0.100000.dat' using 1:2 with lines ls 2 title "Krok = 0.1", 'metodaJawnaEulera__T=1.000000.dat' using 1:2 with lines ls 3 title "Krok = 1.0", 'rozwiazanie_analityczne.dat' using 1:2 with lines ls 4 title "Rozwiazanie analityczne"
#############################################################################################################
set title "Zmiana bledu globalnego metody jawnej Eulera" # tytul wykresu
set output "blad_globalny_Euler.jpg" # nazwa pliku wynikowego

plot 'metodaJawnaEulera__T=0.010000.dat' using 1:3 with lines title "Krok = 0.01" ls 1, 'metodaJawnaEulera__T=0.100000.dat' using 1:3 with lines ls 2 title "Krok = 0.1", 'metodaJawnaEulera__T=1.000000.dat' using 1:3 with lines ls 3 title "Krok = 1.0"
#############################################################################################################
set title "Metoda RK2" # tytul wykresu
set output "MetodaRK2.jpg" # nazwa pliku wynikowego

plot 'metodaRK2__T=0.010000.dat' using 1:2 with lines title "Krok = 0.01" ls 1, 'metodaRK2__T=0.100000.dat' using 1:2 with lines ls 2 title "Krok = 0.1", 'metodaRK2__T=1.000000.dat' using 1:2 with lines ls 3 title "Krok = 1.0", 'rozwiazanie_analityczne.dat' using 1:2 with lines ls 4 title "Rozwiazanie analityczne"
#############################################################################################################
set title "Zmiana bledu globalnego metody jawnej Eulera" # tytul wykresu
set output "blad_globalny_RK2.jpg" # nazwa pliku wynikowego

plot 'metodaRK2__T=0.010000.dat' using 1:3 with lines title "Krok = 0.01" ls 1, 'metodaRK2__T=0.100000.dat' using 1:3 with lines ls 2 title "Krok = 0.1", 'metodaRK2__T=1.000000.dat' using 1:3 with lines ls 3 title "Krok = 1.0"
#############################################################################################################
set title "Metoda RK4" # tytul wykresu
set output "MetodaRK4.jpg" # nazwa pliku wynikowego

plot 'metodaRK4__T=0.010000.dat' using 1:2 with lines title "Krok = 0.01" ls 1, 'metodaRK4__T=0.100000.dat' using 1:2 with lines ls 2 title "Krok = 0.1", 'metodaRK4__T=1.000000.dat' using 1:2 with lines ls 3 title "Krok = 1.0", 'rozwiazanie_analityczne.dat' using 1:2 with lines ls 4 title "Rozwiazanie analityczne"
#############################################################################################################
set title "Zmiana bledu globalnego metody jawnej Eulera" # tytul wykresu
set output "blad_globalny_RK4.jpg" # nazwa pliku wynikowego

plot 'metodaRK4__T=0.010000.dat' using 1:3 with lines title "Krok = 0.01" ls 1, 'metodaRK4__T=0.100000.dat' using 1:3 with lines ls 2 title "Krok = 0.1", 'metodaRK4__T=1.000000.dat' using 1:3 with lines ls 3 title "Krok = 1.0"
#############################################################################################################
set title "RLC_I_porownanie" # tytul wykresu
set output "RLC_I_comp.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=0.500000.dat' using 1:2 with lines title "I(t), 0.5" ls 2, 'RLC_OmegaV=0.800000.dat' using 1:2 with lines ls 4 title "I(t), 0.8", 'RLC_OmegaV=1.000000.dat' using 1:2 with lines ls 6 title "I(t), 1.0", 'RLC_OmegaV=1.200000.dat' using 1:2 with lines ls 8 title "I(t), 1.2"
#############################################################################################################
set title "RLC_Q_porownanie" # tytul wykresu
set output "RLC_Q_comp.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=0.500000.dat' using 1:3 with lines ls 2 title "Q(t), 0.5", 'RLC_OmegaV=0.800000.dat' using 1:3 with lines ls 4 title "Q(t), 0.8", 'RLC_OmegaV=1.000000.dat' using 1:3 with lines ls 6 title "Q(t), 1.0", 'RLC_OmegaV=1.200000.dat' using 1:3 with lines ls 8 title "Q(t), 1.2"
#############################################################################################################
set title "RLC, 0.5 Q" # tytul wykresu
set output "RLC_0.5_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=0.500000.dat' using 1:3 with lines title "Q(t)" ls 1
#############################################################################################################
set title "RLC, 0.5 I,Q" # tytul wykresu
set output "RLC_0.5_I_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=0.500000.dat' using 1:2 with lines title "I(t)" ls 1, 'RLC_OmegaV=0.500000.dat' using 1:3 with lines ls 2 title "Q(t)"
#############################################################################################################
set title "RLC, 0.8 Q" # tytul wykresu
set output "RLC_0.8_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=0.800000.dat' using 1:3 with lines title "Q(t)" ls 1
#############################################################################################################
set title "RLC, 0.8 I,Q" # tytul wykresu
set output "RLC_0.8_I_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=0.800000.dat' using 1:2 with lines title "I(t)" ls 1, 'RLC_OmegaV=0.800000.dat' using 1:3 with lines ls 2 title "Q(t)"
#############################################################################################################
set title "RLC, 1.0 Q" # tytul wykresu
set output "RLC_1.0_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=1.000000.dat' using 1:3 with lines title "Q(t)" ls 1
#############################################################################################################
set title "RLC, 1.0 I,Q" # tytul wykresu
set output "RLC_1.0_I_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=1.000000.dat' using 1:2 with lines title "I(t)" ls 1, 'RLC_OmegaV=1.000000.dat' using 1:3 with lines ls 2 title "Q(t)"
#############################################################################################################
set title "RLC, 1.2 Q" # tytul wykresu
set output "RLC_1.2_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=1.200000.dat' using 1:3 with lines title "Q(t)" ls 1
#############################################################################################################
set title "RLC, 1.2 I,Q" # tytul wykresu
set output "RLC_1.2_I_Q.jpg" # nazwa pliku wynikowego

plot 'RLC_OmegaV=1.200000.dat' using 1:2 with lines title "I(t)" ls 1, 'RLC_OmegaV=1.200000.dat' using 1:3 with lines ls 2 title "Q(t)"
#############################################################################################################

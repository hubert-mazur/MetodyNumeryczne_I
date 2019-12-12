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

set view map
unset contour

set title "nx = ny = 50, rho=0, eps1 = eps2 = 1"
set out "5a.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'V_rho_null=1_eps1=1.000000_eps2=1.000000_nx_ny=50_50.dat' u 1:2:3 w pm3d

#############################################################################################################

set view map
unset contour

set title "nx = ny = 100, rho=0, eps1 = eps2 = 1"
set out "5b.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'V_rho_null=1_eps1=1.000000_eps2=1.000000_nx_ny=100_100.dat' u 1:2:3 w pm3d

#############################################################################################################

set view map
unset contour

set title "nx = ny = 200, rho=0, eps1 = eps2 = 1"
set out "5c.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'V_rho_null=1_eps1=1.000000_eps2=1.000000_nx_ny=200_200.dat' u 1:2:3 w pm3d

#############################################################################################################

set view map
unset contour

set title "nx = ny = 100, rho!=0, eps1 = eps2 = 1"
set out "6a.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'V_rho_null=0_eps1=1.000000_eps2=1.000000_nx_ny=100_100.dat' u 1:2:3 w pm3d

#############################################################################################################

set view map
unset contour

set title "nx = ny = 100, rho!=0, eps1 =1,  eps2 = 2"
set out "6b.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'V_rho_null=0_eps1=1.000000_eps2=2.000000_nx_ny=100_100.dat' u 1:2:3 w pm3d

#############################################################################################################

set view map
unset contour

set title "nx = ny = 100, rho!=0, eps1 =1,  eps2 = 10"
set out "6c.jpg"
set palette defined (-1 'blue', 0 'white', 1 'red')
splot 'V_rho_null=0_eps1=1.000000_eps2=10.000000_nx_ny=100_100.dat' u 1:2:3 w pm3d
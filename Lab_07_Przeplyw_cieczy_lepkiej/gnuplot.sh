#!/usr/bin/env bash
set terminal post enhanced colour solid font 14 size 800, 600  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set terminal jpeg



unset key

################################################### DRAW ####################################################

#############################################################################################################
# psi -4000
set view map
set contour
unset surface
set cntrparam levels 30


set title "psi, Q_in =- -4000"
set out "psi_Q_in_-4000.jpg"
splot 'Q_in=-4000.000000.dat' u 1:2:3:3 w pm3d

#############################################################################################################
# dzeta -4000

set view map
set contour
set cntrparam levels 30
unset surface
set title "dzeta, Q_in =- -4000"
set out "dzeta_Q_in_-4000.jpg"
splot 'Q_in=-4000.000000.dat' u 1:2:4:4 w pm3d

#############################################################################################################
# u
set view map
set contour
set cntrparam levels 40
unset contour
set surface
set title "u(x,y), Q_in =- -4000"
set out "u(x,y)_Q_in_-4000.jpg"
splot 'Q_in=-4000.000000.dat' u 1:2:5:5 w pm3d

#############################################################################################################
# v
set view map
set contour
set cntrparam levels 40
unset contour
set surface

set title "v(x,y), Q_in =- -4000"
set out "v(x,y)_Q_in_-4000.jpg"
splot 'Q_in=-4000.000000.dat' u 1:2:6:6 w pm3d

#############################################################################################################
#############################################################################################################

# psi -1000
set view map
set contour
unset surface
set cntrparam levels 40


set title "psi, Q_in =- -1000"
set out "psi_Q_in_-1000.jpg"
splot 'Q_in=-1000.000000.dat' u 1:2:3 w pm3d

#############################################################################################################
# dzeta -1000

set view map
set contour
set cntrparam levels 40

set title "dzeta, Q_in =- -1000"
set out "dzeta_Q_in_-1000.jpg"
splot 'Q_in=-1000.000000.dat' u 1:2:4 w pm3d

#############################################################################################################
# u
set view map
set contour
set cntrparam levels 40
unset contour
set surface
set title "u(x,y), Q_in =- -1000"
set out "u(x,y)_Q_in_-1000.jpg"
splot 'Q_in=-1000.000000.dat' u 1:2:5:5 w pm3d

#####################################################surface########################################################
# v
set view map
set contour
set cntrparam levels 40
unset contour
set surface
set title "v(x,y), Q_in =- -1000"
set out "v(x,y)_Q_in_-1000.jpg"
splot 'Q_in=-1000.000000.dat' u 1:2:6:6 w pm3d

#############################################################################################################
#############################################################################################################
# psi 4000
set view map
set contour
set cntrparam levels 40
unset surface

set title "psi, Q_in = 4000"
set out "psi_Q_in_4000.jpg"
splot 'Q_in=4000.000000.dat' u 1:2:3:3 w pm3d
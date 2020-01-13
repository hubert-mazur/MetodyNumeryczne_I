#!/usr/bin/env bash
set terminal post enhanced colour solid font 14 size 800, 600  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set terminal jpeg

unset key

################################################### DRAW ####################################################

#############################################################################################################
# set view map
# set contour
# unset surface
# set cntrparam levels 30


set title "predkosci"
set out "predkosci.jpg"
splot 'test.dat' u 1:2:3:3 w pm3d

#############################################################################################################

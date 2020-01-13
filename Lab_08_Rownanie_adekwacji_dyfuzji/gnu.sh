set terminal post enhanced colour solid font 20  

set out "wyniki.eps"

unset key
# Vx (x,y) i Vy(x,y)
set view map
set contour
set cntrparam levels 40
unset contour
set surface
unset key
set title "V_x (x,y) V_y(x,y) D = 0"
splot 'test.dat' u 1:2:3:4 w pm3d

# # Vx (x,y) i Vy(x,y)
# set view map
# set contour
# set cntrparam levels 40
# unset contour
# set surface
# unset key
# set title "V_x (x,y) V_y(x,y) D = 0.1"
# splot 'zad2v.txt' u 1:2:3:4 w pm3d

# c xs
set view map
set contour
unset surface
set cntrparam levels 30
set key
set title "c(t), x_{sr}(t) dla D = 0 i D = 0.1"
plot 'calka_D=0.000000IT_MAX=10000.dat' u 1:2 w l lc 1 t "C(t_n), D = 0",\
    #  'zad2c.txt' u 1:2 w l lc 2 t "C(t_n), D = 0.1",\
     'xsr_D=0.000000IT_MAX=10000.txt' u 1:2 w l lc 3 t "X_{sr}(t_n), D = 0",\
    #  'zad2xsr.txt' u 1:2 w l lc 4 t "X_{sr}(t_n), D = 0.1",\

# MAPY
set view map
set contour
set cntrparam levels 40
unset contour
set surface
unset key
#D = 0
set title "k = 1, D = 0"
splot 'mapa_D=0.000000IT_MAX=10000.dat' u 1:2:3 w pm3d

# set title "k = 2, D = 0"
# splot 'zad1k2.txt' u 1:2:3 w pm3d

# set title "k = 3, D = 0"
# splot 'zad1k3.txt' u 1:2:3 w pm3d

# set title "k = 4, D = 0"
# splot 'zad1k4.txt' u 1:2:3 w pm3d

# set title "k = 5, D = 0"
# splot 'zad1k5.txt' u 1:2:3 w pm3d

#D = 0.1
# set title "k = 1, D = 0.1"
# splot 'zad2k1.txt' u 1:2:3 w pm3d

# set title "k = 2, D = 0.1"
# splot 'zad2k2.txt' u 1:2:3 w pm3d

# set title "k = 3, D = 0.1"
# splot 'zad2k3.txt' u 1:2:3 w pm3d

# set title "k = 4, D = 0.1"
# splot 'zad2k4.txt' u 1:2:3 w pm3d

# set title "k = 5, D = 0.1"
# splot 'zad2k5.txt' u 1:2:3 w pm3d
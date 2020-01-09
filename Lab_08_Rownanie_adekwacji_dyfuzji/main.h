//
// Created by hubert on 09.01.20.
//

#ifndef LAB_08_ROWNANIE_ADEKWACJI_DYFUZJI_MAIN_H
#define LAB_08_ROWNANIE_ADEKWACJI_DYFUZJI_MAIN_H

#include <fstream>
#include <iostream>
#include <cmath>

const int nx = 400;
const int ny = 90;
const int i1 = 200;
const int i2 = 210;
const int j2 = 50;
const double delta = 0.01;
const double sigma = 10 * delta;
const double xA = 0.45;
const double yA = 0.45;

void solve_AD_equation_(double D, int IT_MAX);
double rozkladGestoci(double x, double y);


#endif //LAB_08_ROWNANIE_ADEKWACJI_DYFUZJI_MAIN_H

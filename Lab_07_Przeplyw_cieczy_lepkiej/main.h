#pragma once
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

const double delta = 0.01;
const double rho = 1;
const double mi = 1;
const int nx = 200;
const int ny = 90;
const int i_1 = 50;
const int j_1 = 55;
const int IT_MAX = 20000;

void init(double ***array, int sizeX, int sizeY, double value = 0);

void del(double ***array, int sizeX);

void warunki_brzegowe_PSI(double **psi, double Q_in, double Q_out, double *y);

void warunki_brzegowe_DZETA(double **dzeta, double **psi, double Q_in, double Q_out, double *y);

void relaksacja_NS(double Q_in);

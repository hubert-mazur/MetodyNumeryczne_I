#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "mgmres.h"

const double delta = 0.1;

void licz_poisson(double, double, double, double, double, double, int, int, bool);

double rho(double x, double y, double xmax, double ymax, double sigma)
{
    double temp;

    temp = -exp(-pow((x - 0.75 * xmax) / (sigma), 2) - pow((y - 0.5 * ymax) / (sigma), 2));
    temp += exp(-pow((x - 0.25 * xmax) / (sigma), 2) - pow((y - 0.5 * xmax) / (sigma), 2));
    return temp;
}

double rho()
{
    return 0.0;
}
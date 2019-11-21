#include <iostream>
#include <stdio.h>
#include <cmath>
#include <utility>
#include <string>

std::pair<double, double> *metoda_trapezow(double xn, double vn, double dT, double alpha)
{
    const double delta = pow(10, -10);
    double xn_1 = xn;
    double vn_1 = vn;
    double dX;
    double dV;

    const double a11 = 1.0;
    const double a12 = -dT / 2.0;
    double a21;
    double a22;
    double F;
    double G;

    while (true)
    {
        F = xn_1 - xn - (dT / 2.0) * (vn + vn_1);
        G = vn_1 - vn - (dT / 2.0) * ((alpha * (1.0 - pow(xn, 2)) * vn - xn) + (alpha * (1.0 - pow(xn_1, 2)) * vn_1 - xn_1));

        a21 = (-dT / 2.0) * (-2.0 * alpha * xn_1 * vn_1 - 1.0);
        a22 = 1.0 - (dT / 2.0) * alpha * (1.0 - pow(xn_1, 2.0));

        dX = ((-F) * a22 - (-G) * a12) / (a11 * a22 - a12 * a21);
        dV = (a11 * (-G) - a21 * (-F)) / (a11 * a22 - a12 * a21);

        xn_1 += dX;
        vn_1 += dV;
        if (dX < delta && dV < delta)
            break;

        // std::cout << dX << " and " << dV << "\n";
    }
    return new std::pair<double, double>(xn_1, vn_1);
}

std::pair<double, double> *metoda_RK2(double xn, double vn, double dT, double alpha)
{
    double k1x = vn;
    double k1v = alpha * (1.0 - pow(xn, 2)) * vn - xn;

    double k2x = vn + dT * k1v;
    double k2v = alpha * (1.0 - pow(xn + dT * k1x, 2)) * (vn + dT * k1v) - (xn + dT * k1x);

    return new std::pair<double, double>(xn + (dT / 2.0) * (k1x + k2x), vn + (dT / 2.0) * (k1v + k2v));
}

void timeControl(double x0, double v0, double dT0, double S, int p, double Tmax, double alpha, std::pair<double, double> *funct(double, double, double, double), std::string metoda)
{
    double xn = x0;
    double vn = v0;
    double dT = dT0;
    double Ex;
    double Ev;

    double TOL[] = {pow(10, -2), pow(10, -5)};
    FILE *(fileArray)[] = {
        fopen(&(metoda + std::to_string(TOL[0]) + ".dat")[0], "w"),
        fopen(&(metoda + std::to_string(TOL[1]) + ".dat")[0], "w")
        };

    std::pair<double, double> *step_n1_2, *step_n_2_2, *step_n_2_1;

    for (int j = 0; j < 2; j++)
    {
        xn = x0;
        vn = v0;

        for (double i = 0.0; i <= Tmax;)
        {
            step_n1_2 = funct(xn, vn, dT, alpha);
            step_n_2_2 = funct(step_n1_2->first, step_n1_2->second, dT, alpha);

            step_n_2_1 = funct(xn, vn, 2.0 * dT, alpha);
            Ex = (step_n_2_2->first - step_n_2_1->first) / (pow(2, p) - 1.0);
            Ev = (step_n_2_2->second - step_n_2_1->second) / (pow(2, p) - 1.0);

            if (fmax(fabs(Ex), fabs(Ev)) < TOL[j])
            {
                i = i + 2.0 * dT;
                xn = step_n_2_2->first;
                vn = step_n_2_2->second;
                fprintf(fileArray[j], "%lf %lf %lf %lf\n", i, dT, xn, vn);
            }
            dT = pow((S * TOL[j]) / (fmax(fabs(Ex), fabs(Ev))), 1.0 / (p + 1.0)) * dT;
            delete step_n1_2;
            delete step_n_2_1;
            delete step_n_2_2;
        }
        fclose(fileArray[j]);
    }
}

int main()
{
    timeControl(0.01, 0, 1, 0.75, 2, 40, 5.0, &metoda_trapezow, "MetodaTrapezow");
    timeControl(0.01, 0, 1, 0.75, 2, 40, 5.0, &metoda_RK2, "MetodaRK2");
}

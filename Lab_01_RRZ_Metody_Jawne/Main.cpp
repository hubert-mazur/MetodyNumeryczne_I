#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <vector>
#include <iomanip>


double rozwiazanieAnalityczne(double arg_t, double lambda)
{
    return exp(lambda * arg_t);
}

void rozwiazanieAnalityczne(double lambda, double timeStart, double timeStop, double timeStamp)
{
    FILE *file = fopen("rozwiazanie_analityczne.dat", "w");

    for (double it = timeStart; it <= timeStop; it += timeStamp)
    {
        fprintf(file, "%lf %lf\n", it, exp(lambda * it));
    }
    fclose(file);
}

void metodaJawnaEulera(double initialValue, double lambda, double timeStart, double timeStop, double timeStamp)
{
    std::string name("metodaJawnaEulera__T=" + std::to_string(timeStamp) + ".dat");

    FILE *file = fopen(&name[0], "w");
    fprintf(file, "krok --- wartosc -- blad_rozwiazania \n");

    double prev = initialValue;
    double curr;

    for (double it = timeStart; it <= timeStop; it += timeStamp)
    {
        curr = prev + timeStamp * lambda * prev;
        fprintf(file, "%lf %lf %lf\n", it, curr, -rozwiazanieAnalityczne(it, lambda) + curr);
        prev = curr;
    }
    fclose(file);
}

void metodaRK2(double initialValue, double lambda, double timeStart, double timeStop, double timeStamp)
{
    std::string name("metodaRK2__T=" + std::to_string(timeStamp) + ".dat");

    FILE *file = fopen(&name[0], "w");
    fprintf(file, "krok --- wartosc -- blad_rozwiazania \n");

    double prev = initialValue;
    double curr;

    for (double it = timeStart; it <= timeStop; it += timeStamp)
    {
        curr = prev + (timeStamp / 2.0) * (lambda * prev + (lambda * (prev + timeStamp * lambda * prev)));
        fprintf(file, "%lf %lf %lf\n", it, curr, -rozwiazanieAnalityczne(it, lambda) + curr);
        prev = curr;
    }
    fclose(file);
}

void metodaRK4(double initialValue, double lambda, double timeStart, double timeStop, double timeStamp)
{
    std::string name("metodaRK4__T=" + std::to_string(timeStamp) + ".dat");

    FILE *file = fopen(&name[0], "w");
    fprintf(file, "krok --- wartosc -- blad_rozwiazania \n");

    double prev = initialValue;
    double curr;

    for (double it = timeStart; it <= timeStop; it += timeStamp)
    {
        double k1 = lambda * prev;
        double k2 = lambda * (prev + timeStamp * k1 / 2.0);
        double k3 = lambda * (prev + timeStamp * k2 / 2.0);
        double k4 = lambda * (prev + timeStamp * k3);
        curr = prev + (timeStamp / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        fprintf(file, "%lf %lf %lf\n", it, curr, -rozwiazanieAnalityczne(it, lambda) + curr);
        prev = curr;
    }
    fclose(file);
}

double V(double omegaV, double T)
{
    return 10 * sin(omegaV * T);
}

void RLC(double R, double L, double C, double deltaT, double initI, double initQ, double omegaV)
{
    double prevI = initI;
    double prevQ = initQ;
    double currI;
    double currQ;
    double k1Q, k2Q, k3Q, k4Q, k1I, k2I, k3I, k4I;
    double omega0 = 1.0 / (sqrt(L * C));

    std::string name = "RLC_OmegaV=" + std::to_string(omegaV) + ".dat";

    FILE *file = fopen(&name[0], "w");
    fprintf(file, "time -- I -- Q -- V\n");

    for (double it = 0; it <= 4 * 2 * M_PI * sqrt(L * C); it += 0.001)
    {
        k1Q = prevI;
        k1I = (V(omega0 * omegaV, it) / L) - (1.0 / (L * C)) * prevQ - (R / L) * prevI;
        k2Q = prevI + (deltaT / 2.0) * k1I;
        k2I = (V(omega0 * omegaV, it + deltaT / 2.0) / L) - (1.0 / (L * C)) * (prevQ + ((deltaT / 2.0) * k1Q)) - (R / L) * (prevI + (deltaT / 2.0) * k1I);
        k3Q = prevI + (deltaT / 2.0) * k2I;
        k3I = (V(omega0 * omegaV, it + deltaT / 2.0) / L) - (1.0 / (L * C)) * (prevQ + ((deltaT / 2.0) * k2Q)) - (R / L) * (prevI + (deltaT / 2.0) * k2I);
        k4Q = prevI + (deltaT * k3I);
        k4I = (V(omega0 * omegaV, it + deltaT) / L) - (1.0 / (L * C)) * (prevQ + ((deltaT)*k3Q)) - (R / L) * (prevI + (deltaT)*k3I);

        currQ = prevQ + (deltaT / 6.0) * (k1Q + 2 * k2Q + 2 * k3Q + k4Q);
        currI = prevI + (deltaT / 6.0) * (k1I + 2 * k2I + 2 * k3I + k4I);

        fprintf(file, "%lf %lf %lf %lf\n", it, currI, currQ, V(omega0 * omegaV, it));
        prevI = currI;
        prevQ = currQ;
    }

    fclose(file);
}

int main()
{
    metodaJawnaEulera(1.0, -1.0, 0.0, 5.0, 0.01);
    metodaJawnaEulera(1.0, -1.0, 0.0, 5.0, 0.1);
    metodaJawnaEulera(1.0, -1.0, 0.0, 5.0, 1.0);
    rozwiazanieAnalityczne(-1.0, 0.0, 5.0, 0.01);
    metodaRK2(1, -1, 0, 5, .01);
    metodaRK2(1, -1, 0, 5, .1);
    metodaRK2(1, -1, 0, 5, 1.0);
    metodaRK4(1, -1, 0, 5, .01);
    metodaRK4(1, -1, 0, 5, .1);
    metodaRK4(1, -1, 0, 5, 1.0);
    RLC(100, 0.1, 0.001, 0.0001, 0, 0, 0.5);
    RLC(100, 0.1, 0.001, 0.0001, 0, 0, 0.8);
    RLC(100, 0.1, 0.001, 0.0001, 0, 0, 1.0);
    RLC(100, 0.1, 0.001, 0.0001, 0, 0, 1.2);

    return 0;
}
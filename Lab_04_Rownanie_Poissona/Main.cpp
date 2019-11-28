#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <vector>
#include <mutex>
#include <thread>

const double epsilon = 1.0;
const double delta = 0.1;
const int nx = 150;
const int ny = 100;
const double v1 = 10.0;
const double v2 = 0.0;
double Xmax = delta * nx;
double Ymax = delta * ny;
double sigmaX = 0.1 * Xmax;
double sigmaY = 0.1 * Ymax;

double p(double x, double y)
{
    double s1, s2;

    s1 = exp(-pow((x - 0.35 * Xmax) / (sigmaX), 2) - pow((y - 0.5 * Ymax) / (sigmaY), 2));
    s2 = -exp(-pow((x - 0.65 * Xmax) / (sigmaX), 2) - pow((y - 0.5 * Ymax) / (sigmaY), 2));

    return s1 + s2;
}

double **init()
{
    double **array;
    array = new double *[nx + 1];

    for (int i = 0; i <= nx; i++)
        array[i] = new double[ny + 1];

    for (int i = 0; i <= nx; i++)
        for (int j = 0; j <= ny; j++)
            array[i][j] = 0.0;
    return array;
}

void del(double **array)
{
    for (int i = 0; i <= nx; i++)
        delete[] array[i];

    delete[] array;
}

double stopCondition(double **V)
{
    double S = 0;

    for (int i = 0; i < nx; i++)
        for (int j = 0; j < ny; j++)
            S += pow(delta, 2) * (0.5 * pow((V[i + 1][j] - V[i][j]) / (delta), 2) + 0.5 * pow((V[i][j + 1] - V[i][j]) / (delta), 2) - V[i][j] * p(i, j));

    return S;
}

void relaksacjaGlobalna(double omegaG, double V, double TOL, double epsilon)
{
    std::vector<double> S;
    int it = 0;

    FILE *file = fopen(&("relaksacja_globalna_omega=" + std::to_string(omegaG) + ".dat")[0], "w");
    FILE *file2 = fopen(&("relaksacja_globalna_S_omega=" + std::to_string(omegaG) + ".dat")[0], "w");
    FILE *file3 = fopen(&("relaksacja_globalna_err_omega=" + std::to_string(omegaG) + ".dat")[0], "w");

    double **V_s, **V_n;

    V_s = init();
    V_n = init();

    for (int i = 0; i <= nx; i++)
    {
        V_s[i][0] = V;
        V_n[i][0] = V;
    }

    S.push_back(0);

    while (true)
    {
        for (int i = 1; i < nx; i++)
        {
            for (int j = 1; j < ny; j++)
            {
                // std::cout << i << " " << j << "\n";
                V_n[i][j] = (1.0 / 4.0) * (V_s[i + 1][j] + V_s[i - 1][j] + V_s[i][j + 1] + V_s[i][j - 1] + (pow(delta, 2) / epsilon) * p(i, j));
            }
        }

        for (int j = 0; j <= ny; j++)
        {
            V_n[0][j] = V_n[1][j];
            V_n[nx][j] = V_n[nx - 1][j];
        }

        for (int i = 0; i <= nx; i++)
            for (int j = 0; j <= ny; j++)
                V_s[i][j] = (1.0 - omegaG) * V_s[i][j] + omegaG * V_n[i][j];

        S.push_back(stopCondition(V_n));

        fprintf(file2, "%d %g\n", it, S.at(it + 1));

        if (it > 0)
        {
            // std::cout << fabs(S.at(it) - S.at(it - 1)) << "\n";
            if (fabs((S[it] - S[it - 1]) / S[it - 1]) < TOL)
                break;
        }
        it++;
    }

    for (int i = 0; i <= nx; i++)
        for (int j = 0; j <= ny; j++)
            fprintf(file, "%d %d %g\n", i, j, V_s[i][j]);

    for (int i = 1; i < nx; i++)
        for (int j = 1; j < ny; j++)
            fprintf(file3, "%d %d %lf\n", i, j, ((V_n[i + 1][j] - 2 * V_n[i][j] + V_n[i - 1][j]) / pow(delta, 2) + (V_n[i][j + 1] - 2 * V_n[i][j] + V_n[i][j - 1]) / pow(delta, 2)) + p(i, j) / epsilon);

    fclose(file);
    fclose(file2);
    fclose(file3);
    del(V_s);
    del(V_n);
}

void relaksacjaLokalna(double omegaL, double V, double TOL, double epsilon)
{
    double **V_n;

    std::vector<double> S;
    int it = 0;

    FILE *file2 = fopen(&("relaksacja_lokalna_S_omega=" + std::to_string(omegaL) + ".dat")[0], "w");

    V_n = init();

    for (int i = 0; i <= nx; i++)
    {
        V_n[i][0] = V;
    }

    S.push_back(1);
    while (true)
    {
        for (int i = 1; i < nx; i++)
            for (int j = 1; j < ny; j++)
                V_n[i][j] = (1.0 - omegaL) * V_n[i][j] + (omegaL / 4.0) * (V_n[i + 1][j] + V_n[i - 1][j] + V_n[i][j + 1] + V_n[i][j - 1] + (pow(delta,2)/epsilon) *p(i, j));

        for (int i = 0; i <= ny; i++)
        {
            V_n[0][i] = V_n[1][i];
            V_n[nx][i] = V_n[nx - 1][i];
        }

        S.push_back(stopCondition(V_n));

        fprintf(file2, "%d %g\n", it, S.at(it));

        if (it > 0)
        {
            // std::cout << fabs(S.at(it) - S.at(it - 1)) << "\n";
            if (fabs((S[it] - S[it - 1]) / S[it - 1]) < TOL)
                break;
        }
        it++;
    }

    del(V_n);
    fclose(file2);
}

int main()
{

    std::thread th1(relaksacjaGlobalna, 0.6, 10, pow(10, -8), 1);
    std::thread th2(relaksacjaGlobalna, 1.0, 10, pow(10, -8), 1);
    std::thread th3(relaksacjaLokalna, 1.0, 10, pow(10, -8), 1);
    std::thread th4(relaksacjaLokalna, 1.4, 10, pow(10, -8), 1);
    std::thread th5(relaksacjaLokalna, 1.8, 10, pow(10, -8), 1);
    std::thread th6(relaksacjaLokalna, 1.9, 10, pow(10, -8), 1);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
}

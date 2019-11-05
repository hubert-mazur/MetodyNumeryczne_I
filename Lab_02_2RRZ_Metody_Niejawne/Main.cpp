#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>

double alpha(double beta, int N, double gamma)
{
    return beta * static_cast<double>(N) - gamma;
}

void metodaPicarda(double beta, int N, double gamma, double Tmax, double dT, double mi0, double TOL, double mi)
{
    double prev;
    double curr;
    prev = mi0;
    double prev_mi = mi0;

    FILE *file = fopen("MetodaPicarda.dat", "w");
    fprintf(file, "time -- u(t) -- z(t) = N - u(t)\n");

    for (double i = 0.0; i <= Tmax; i += dT)
    {
        while (true)
        {
            curr = prev + (dT / 2.0) * ((alpha(beta, N, gamma) * prev - (beta * pow(prev, 2)) + (alpha(beta, N, gamma) * prev_mi - beta * (pow(prev_mi, 2)))));
            if (fabs(curr - prev_mi) <= TOL || --mi >= 0)
                break;
            else
            {
                prev_mi = curr;
            }
        }
        fprintf(file, "%lf %lf %lf\n", i, curr, N - curr);
        prev = curr;
        prev_mi = curr;
    }
    fclose(file);
}

void metodaNewtona(double beta, int N, double gamma, double Tmax, double dT, double mi0, double TOL, double mi)
{
    double prev;
    double curr;
    prev = mi0;
    double prev_mi = mi0;

    FILE *file = fopen("MetodaNewtona.dat", "w");
    fprintf(file, "time -- u(t) -- z(t) = N - u(t)\n");

    for (double i = 0.0; i <= Tmax; i += dT)
    {
        while (true)
        {
            curr = prev_mi - ((prev_mi - prev - (dT / 2.0) * ((alpha(beta, N, gamma) * prev - beta * pow(prev, 2)) + (alpha(beta, N, gamma) * prev_mi - beta * (pow(prev_mi, 2))))) / (1.0 - (dT / 2.0) * (alpha(beta, N, gamma) - 2 * beta * prev_mi)));
            if (fabs(curr - prev_mi) <= TOL || --mi >= 0)
                break;
            else
            {
                prev_mi = curr;
            }
        }
        fprintf(file, "%lf %lf %lf\n", i, curr, N - curr);
        prev = curr;
        prev_mi = curr;
    }
    fclose(file);
}

double function(double beta, int N, double gamma, double u)
{
    return (u * (beta * N - gamma) - beta * pow(u, 2));
}

void metodaRK2Niejawna(double beta, int N, double gamma, double Tmax, double dT, double mi0, double TOL, double mi)
{
    const double a[2][2] = {1 / 4.0, 1 / 4.0 - sqrt(3) / 3.0,
                            1 / 4.0 - sqrt(3) / 3.0, 1 / 4.0};

    const double c[2] = {1 / 2.0 - sqrt(3) / 6.0,
                         1 / 2.0 + sqrt(3) / 6.0};

    const double b[2] = {1 / 2.0,
                         1 / 2.0};

    double prev_U1 = mi0;
    double prev_U1_mi = mi0;
    double prev_U2 = mi0;
    double prev_U2_mi = mi0;
    double curr_U1;
    double curr_U2;
    double prev = mi0;
    double curr;
    double F1;
    double F2;
    double dU1;
    double dU2;
    double m[2][2];

    FILE *file = fopen("Metoda_RK2.dat", "w");

    fprintf(file, "time -- u(t) -- z(t) = N - u(t)\n");

    for (double i = 0; i <= Tmax; i += dT)
    {
        F1 = prev_U1 - prev - dT * (a[0][0] * (alpha(beta, N, gamma) * prev_U1 - beta * pow(prev_U1, 2)) + a[0][1] * (alpha(beta, N, gamma) * prev_U2 - beta * pow(prev_U2, 2)));
        F2 = prev_U2 - prev - dT * (a[1][0] * (alpha(beta, N, gamma) * prev_U1 - beta * pow(prev_U1, 2)) + a[1][1] * (alpha(beta, N, gamma) * prev_U2 - beta * pow(prev_U2, 2)));

        m[0][0] = 1.0 - dT * a[0][0] * (alpha(beta, N, gamma) - 2 * beta * prev_U1);
        m[0][1] = -dT * a[0][1] * (alpha(beta, N, gamma) - 2 * beta * prev_U2);
        m[1][0] = -dT * a[1][0] * (alpha(beta, N, gamma) - 2 * beta * prev_U1);
        m[1][1] = 1.0 - dT * a[1][1] * (alpha(beta, N, gamma) - 2 * beta * prev_U2);

        while (true)
        {
            dU1 = (F2 * m[0][1] - F1 * m[1][1]) / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
            dU2 = (F1 * m[1][0] - F2 * m[0][0]) / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
            curr_U1 = prev_U1_mi + dU1;
            curr_U2 = prev_U2_mi + dU2;
            if ((fabs(curr_U1 - prev_U1_mi) <= TOL && fabs(curr_U2 - prev_U2_mi) <= TOL) || --mi < 0)
                break;
            prev_U1_mi = curr_U1;
            prev_U2_mi = curr_U2;
        }

        curr = prev + dT * (b[0] * function(beta, N, gamma, curr_U1) + b[1] * function(beta, N, gamma, curr_U2));
        fprintf(file, "%lf %lf %lf\n", i, curr, N - curr);
        prev = curr;
    }
    fclose(file);
}

int main()
{
    metodaPicarda(0.001, 500, 0.1, 100, 0.1, 1, pow(10, -6), 20);
    metodaNewtona(0.001, 500, 0.1, 100, 0.1, 1, pow(10, -6), 20);
    metodaRK2Niejawna(0.001, 500, 0.1, 100, 0.1, 1, pow(10, -6), 20);
    return 0;
}
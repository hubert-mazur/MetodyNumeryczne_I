#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

const double delta = 0.2;
const int nx = 128;
const int ny = 128;
const double xmax = delta * nx;
const double ymax = delta * ny;
const double TOL = pow(10, -8);

void warunki_brzegowe(double ***array)
{

    for (int i = 0; i <= nx; i++)
    {
        (*array)[0][i] = sin(M_PI * ((delta * i) / ymax));
        (*array)[i][0] = sin(2 * M_PI * ((delta * i) / xmax));
        (*array)[nx][i] = sin(M_PI * ((delta * i) / ymax));
        (*array)[i][ny] = -sin(2 * M_PI * ((delta * i) / xmax));
    }
}

double stopCondition(double **V, int k)
{
    double S = 0;

    for (int i = 0; i <= nx - k; i += k)
        for (int j = 0; j <= ny - k; j += k)
            S += (pow(k * delta, 2) / 2.0) * (pow((V[i + k][j] - V[i][j]) / (2 * k * delta) + (V[i + k][j + k] - V[i][j + k]) / (2 * k * delta), 2) + pow((V[i][j + k] - V[i][j]) / (2 * k * delta) + (V[i + k][j + k] - V[i + k][j]) / (2 * k * delta), 2));

    return S;
}

double **init()
{
    double **array;

    array = new double *[nx + 1];

    for (int i = 0; i <= nx; i++)
        array[i] = new double[ny];

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

void relaksacja(double ***V, int k)
{

    std::vector<double> S;
    int it = 0;

    std::fstream potencjal;
    std::fstream iteracje;

    potencjal.open("potencjal_k=" + std::to_string(k) + ".dat", std::ios::out);
    iteracje.open("iteracje_k=" + std::to_string(k) + ".dat", std::ios::out);

    S.push_back(1);

    while (true)
    {
        it++;
        for (int i = k; i <= nx - k; i += k)
            for (int j = k; j <= ny - k; j += k)
                (*V)[i][j] = 0.25 * ((*V)[i + k][j] + (*V)[i - k][j] + (*V)[i][j + k] + (*V)[i][j - k]);

        S.push_back(stopCondition((*V), k));


        iteracje << it << " " << S.at(it) << "\n";

        // std::cout << S.at(it) << std::endl;

        if (fabs((S.at(it) - S.at(it - 1)) / S.at(it - 1)) < TOL)
            break;
    }

    for (int i = 0; i <= nx; i++) {
        for (int j = 0; j <= ny; j++)
            potencjal << i << " " << j << " " << (*V)[i][j] << "\n";
        potencjal << "\n";
    }


    if (k != 1)
    {
        for (int i = 0; i < nx - k; i += k)
        {
            for (int j = 0; j < ny - k; j += k)
            {
                (*V)[i + k / 2][j + k / 2] = 0.25 * ((*V)[i][j] + (*V)[i + k][j] + (*V)[i][j + k] + (*V)[i + k][j + k]);
                (*V)[i + k][j + k / 2] = 0.5 * ((*V)[i + k][j] + (*V)[i + k][j + k]);
                (*V)[i + k / 2][j + k] = 0.5 * ((*V)[i][j + k] + (*V)[i + k][j + k]);
                (*V)[i + k / 2][j] = 0.5 * ((*V)[i][j] + (*V)[i + k][j]);
                (*V)[i][j + k / 2] = 0.5 * ((*V)[i][j] + (*V)[i][j + k]);
            }
        }
    }

    iteracje.close();
    potencjal.close();
}

int main()
{
    double **V = init();

    warunki_brzegowe(&V);

    relaksacja(&V, 16);
    relaksacja(&V, 8);
    relaksacja(&V, 4);
    relaksacja(&V, 2);
    relaksacja(&V, 1);

    del (V);
}

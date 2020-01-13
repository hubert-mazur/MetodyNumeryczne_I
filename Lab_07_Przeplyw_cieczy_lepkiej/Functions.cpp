#include "main.h"
void init(double ***array, int sizeX, int sizeY, double value)
{
    (*array) = new double *[sizeX];

    for (int i = 0; i < sizeX; i++)
        (*array)[i] = new double[sizeY];

    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
            (*array)[i][j] = 0.0;
}

void del(double ***array, int sizeX)
{
    for (int i = 0; i < sizeX; i++)
        delete[](*array)[i];

    delete[](*array);
}

void warunki_brzegowe_PSI(double **psi, double Q_in, double Q_out, double *y)
{
    // brzeg A

    for (int j = j_1; j <= ny; j++)
        psi[0][j] = (Q_in / (2 * mi)) * (pow(y[j], 3) / 3 - (pow(y[j], 2) / 2) * (y[j_1] + y[ny]) + y[j] * y[j_1] * y[ny]);

    // brzeg C

    for (int j = 0; j <= ny; j++)
        psi[nx][j] = (Q_out / (2 * mi)) * (pow(y[j], 3) / 3 - (pow(y[j], 2) / 2) * y[ny]) + (Q_in * pow(y[j_1], 2) * (-y[j_1] + 3 * y[ny])) / (12 * mi);

    // brzeg B

    for (int i = 1; i < nx; i++)
        psi[i][ny] = psi[0][ny];

    // brzeg D

    for (int i = i_1; i < nx; i++)
        psi[i][0] = psi[0][j_1];

    // brzeg E

    for (int j = 1; j <= j_1; j++)
        psi[i_1][j] = psi[0][j_1];

    // brzeg F

    for (int i = 1; i <= i_1; i++)
        psi[i][j_1] = psi[0][j_1];
}

void warunki_brzegowe_DZETA(double **dzeta, double **psi, double Q_in, double Q_out, double *y)
{
    // brzeg A

    for (int j = j_1; j <= ny; j++)
        dzeta[0][j] = (Q_in / (2 * mi)) * (2 * y[j] - y[j_1] - y[ny]);

    // brzeg C

    for (int j = 0; j <= ny; j++)
        dzeta[nx][j] = (Q_out / (2 * mi) * (2 * y[j] - y[ny]));

    // brzeg B

    for (int i = 1; i < nx; i++)
        dzeta[i][ny] = (2 / pow(delta, 2)) * (psi[i][ny - 1] - psi[i][ny]);

    // brzeg D

    for (int i = i_1 + 1; i < nx; i++)
        dzeta[i][0] = (2 / pow(delta, 2)) * (psi[i][1] - psi[i][0]);

    // brzeg E

    for (int j = 1; j < j_1; j++)
        dzeta[i_1][j] = (2 / pow(delta, 2)) * (psi[i_1 + 1][j] - psi[i_1][j]);

    // brzeg F

    for (int i = 1; i <= i_1; i++)
        dzeta[i][j_1] = (2 / pow(delta, 2)) * (psi[i][j_1 + 1] - psi[i][j_1]);

    // wierzcholek E/F

    dzeta[i_1][j_1] = (1 / 2.0) * (dzeta[i_1 - 1][j_1] + dzeta[i_1][j_1 - 1]);
}

void relaksacja_NS(double Q_in)
{
    std::vector<double> y;
    double **psi, **dzeta, **u, **v;
    double gamma;
    double Q_out;
    int omega;
    bool border;
    bool inside;

    std::fstream file;

    file.open("Q_in=" + std::to_string(Q_in) + ".dat", std::ios::out);

    for (int i = 0; i <= ny; i++)
        y.push_back(delta * i);

    Q_out = Q_in * (pow(y[ny], 3) - pow(y[j_1], 3) - 3 * y[j_1] * pow(y[ny], 2) + 3 * pow(y[j_1], 2) * y[ny]) / (pow(y[ny], 3));

    init(&psi, nx + 1, ny + 1);
    init(&dzeta, nx + 1, ny + 1);
    init(&u, nx + 1, ny + 1);
    init(&v, nx + 1, ny + 1);

    warunki_brzegowe_PSI(psi, Q_in, Q_out, &y[0]);

    // file << "i "
    //      << "j "
    //      << "psi "
    //      << "ksi "
    //      << "dPSI/dy "
    //      << "-dPSI/dx" << std::endl;

    for (int it = 1; it < IT_MAX; it++)
    {
        gamma = 0;

        omega = (it < 2000) ? 0 : 1;

        for (int i = 1; i < nx; i++)
        {
            for (int j = 1; j < ny; j++)
            {
                border = (((i <= i_1) && (j == j_1)) || ((i == i_1) && (j <= j_1)));
                inside = !((i <= i_1) && (j < j_1));

                if ((!border && inside))
                {
                    psi[i][j] = 0.25 * (psi[i + 1][j] + psi[i - 1][j] + psi[i][j + 1] + psi[i][j - 1] - pow(delta, 2) * dzeta[i][j]);
                    dzeta[i][j] = 0.25 * (dzeta[i + 1][j] + dzeta[i - 1][j] + dzeta[i][j + 1] + dzeta[i][j - 1]) -
                                  omega * (rho / (16 * mi)) * ((psi[i][j + 1] - psi[i][j - 1]) * (dzeta[i + 1][j] - dzeta[i - 1][j]) - (psi[i + 1][j] - psi[i - 1][j]) * (dzeta[i][j + 1] - dzeta[i][j - 1]));
                    u[i][j] = (psi[i][j + 1] - psi[i][j - 1]) / (2 * delta);
                    v[i][j] = -(psi[i + 1][j] - psi[i - 1][j]) / (2 * delta);
                }
                else
                {
                    u[i][j] = 0;
                    v[i][j] = 0;
                }
            }
        }

        warunki_brzegowe_DZETA(dzeta, psi, Q_in, Q_out, &y[0]);

        for (int i = 1; i < nx; i++)
            gamma += (psi[i + 1][j_1 + 2] + psi[i - 1][j_1 + 2] + psi[i][j_1 + 3] + psi[i][j_1 + 1] - 4 * psi[i][j_1 + 2] - pow(delta, 2) * dzeta[i][j_1 + 2]);

        std::cout << gamma << std::endl;
    }

    for (int i = 1; i < nx; i++)
    {
        for (int j = 1; j < ny; j++)
            if (i <= i_1 && j <= j_1)
                file << i << " " << j << " " << psi[i_1][j_1] << " " << dzeta[i_1][j_1] << " " << u[i][j] << " " << v[i][j] << std::endl;
            else
                file << i << " " << j << " " << psi[i][j] << " " << dzeta[i][j] << " " << u[i][j] << " " << v[i][j] << std::endl;

        file << std::endl;
    }
    del(&psi, nx + 1);
    del(&dzeta, nx + 1);
    del(&u, nx + 1);
    del(&v, nx + 1);
    file.close();
}
#include "headers.h"

int main()
{
    licz_poisson(1, 1, 10, -10, 10, -10, 50, 50, true);
    licz_poisson(1, 1, 10, -10, 10, -10, 100, 100, true);
    licz_poisson(1, 1, 10, -10, 10, -10, 200, 200, true);
    licz_poisson(1, 1, 0, 0, 0, 0, 100, 100, false);
    licz_poisson(1, 2, 0, 0, 0, 0, 100, 100, false);
    licz_poisson(1, 10, 0, 0, 0, 0, 100, 100, false);
    licz_poisson(1, 1, 10, -10, 10, -10,4, 4, true);
}

void licz_poisson(double epsilon1, double epsilon2, double V1, double V2, double V3, double V4, int nx, int ny, bool rho_null)
{
    int N = (nx + 1) * (ny + 1);
    int i;
    int j;

    std::vector<double> a = std::vector<double>(5 * N);
    std::vector<int> ja = std::vector<int>(5 * N);
    std::vector<int> ia = std::vector<int>(N + 1);
    std::vector<double> b = std::vector<double>(N);
    std::vector<double> V = std::vector<double>(N);
    std::vector<double> epsilonL = std::vector<double>(N + nx + 1);
    std::fstream file_a;
    std::fstream file_b;
    std::fstream file_V;

    file_a.open("a_rho_null=" + std::to_string(rho_null) + "_eps1=" + std::to_string(epsilon1) + "_eps2=" +
                    std::to_string(epsilon2) + "_nx_ny=" + std::to_string(nx) + "_" + std::to_string(ny) + ".dat",
                std::ios::out);

    file_b.open("b_rho_null=" + std::to_string(rho_null) + "_eps1=" + std::to_string(epsilon1) + "_eps2=" +
                    std::to_string(epsilon2) + "_nx_ny=" + std::to_string(nx) + "_" + std::to_string(ny) + ".dat",
                std::ios::out);

    file_V.open("V_rho_null=" + std::to_string(rho_null) + "_eps1=" + std::to_string(epsilon1) + "_eps2=" +
                    std::to_string(epsilon2) + "_nx_ny=" + std::to_string(nx) + "_" + std::to_string(ny) + ".dat",
                std::ios::out);

    for (auto i : ia)
        i = -1;

    for (int l = 0; l < N + nx + 1; l++)
    {
        j = floor(static_cast<double>(l) / (nx + 1));
        i = l - j * (nx + 1);
        epsilonL[l] = (i <= nx / 2 ? epsilon1 : epsilon2);
    }

    int k = -1;
    bool brzeg;
    double Vb;
    int nz_num;

    for (int l = 0; l < N; l++)
    {
        j = floor(static_cast<double>(l) / (nx + 1));
        i = l - j * (nx + 1);

        brzeg = false;
        Vb = 0.0;

        if (i == 0)
        {
            brzeg = true;
            Vb = V1;
        }

        if (j == ny)
        {
            brzeg = true;
            Vb = V2;
        }

        if (i == nx)
        {
            brzeg = true;
            Vb = V3;
        }

        if (j == 0)
        {
            brzeg = true;
            Vb = V4;
        }

        b[l] = rho_null ? rho() : rho(i * delta, j * delta, delta * nx, delta * ny, delta * nx / 10.0);

        if (brzeg)
            b[l] = Vb;

        ia[l] = -1;

        // lewa skrajna przekatna

        if ((l - nx - 1) >= 0 && !brzeg)
        {
            k++;
            if (ia[l] < 0)
                ia[l] = k;
            a[k] = epsilonL[l] / pow(delta, 2);
            ja[k] = l - nx - 1;
        }

        // //poddiagonala

        if ((l - 1) >= 0 && !brzeg)
        {
            k++;
            if (ia[l] < 0)
                ia[l] = k;
            a[k] = epsilonL[l] / pow(delta, 2);
            ja[k] = l - 1;
        }

        // diagonala

        k++;
        if (ia[l] < 0)
            ia[l] = k;
        if (!brzeg)
            a[k] = -(2 * epsilonL[l] + epsilonL[l + 1] + epsilonL[l + nx + 1]) / pow(delta, 2);
        else
            a[k] = 1;

        ja[k] = l;

        // naddiagonala

        if (l < N && !brzeg)
        {
            k++;
            a[k] = epsilonL[l + 1] / pow(delta, 2);
            ja[k] = l + 1;
        }

        // prawa skrajna przekatna

        if (l < (N - nx - 1) && !brzeg)
        {
            k++;
            a[k] = epsilonL[l + nx + 1] / pow(delta, 2);
            ja[k] = l + nx + 1;
        }

        if (a[l] > pow(10, -10))
            file_a << l << " " << i << " " << j << " " << a[l] << "\n";
        if (b[l] > pow(10, -10))
            file_b << l << " " << i << " " << j << " " << b[l] << "\n";
    }
    nz_num = k + 1;
    ia[N] = nz_num;

    file_a.close();
    file_b.close();

    pmgmres_ilu_cr(N, nz_num, &ia[0], &ja[0], &a[0], &V[0], &b[0], 500, 500, pow(10, -8), pow(10, -8));

    for (int l = 0; l < N; l++)
    {
        j = floor(static_cast<double>(l) / (nx + 1));
        i = l - j * (nx + 1);

        file_V << i << " " << j << " " << V[l] << std::endl;
        if (i == nx)
            file_V << std::endl;
    }

    file_V.close();
}

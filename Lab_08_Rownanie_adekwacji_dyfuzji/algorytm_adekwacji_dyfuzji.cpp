//
// Created by hubert on 09.01.20.
//

#include "main.h"

void solve_AD_equation_(double D, int IT_MAX)
{
	// utworzenie tablic

	double u0[nx + 1][ny + 1];
	double u1[nx + 1][ny + 1];
	double psi[nx + 1][ny + 1];
	double vx[nx + 1][ny + 1];
	double vy[nx + 1][ny + 1];
	double vMax, deltaT;

	// wczytanie funkcji strumienia

	std::fstream inputFile;
	std::fstream calka;
	std::fstream sredniePolozeniePakietu;
	std::fstream mapaRozkladu;

	inputFile.open("../psi.dat");
	calka.open("../calka_D=" + std::to_string(D) + "IT_MAX=" + std::to_string(IT_MAX), std::ios::out);
	sredniePolozeniePakietu.open("../xsr_D=" + std::to_string(D) + "IT_MAX=" + std::to_string(IT_MAX), std::ios::out);
	mapaRozkladu.open("../mapa_D=" + std::to_string(D) + "IT_MAX=" + std::to_string(IT_MAX), std::ios::out);

	if (inputFile.fail())
	{
		std::cout << "not ok";
		return;
	}

	// wczytanie funkcji strumienia
	{
		int a, b;
		for (int i = 0; i <= nx; i++)
			for (int j = 0; j <= nx; j++)
				inputFile >> a >> b >> psi[i][j];
	}

	// wyznaczenie pola predkosci
	for (int i = 0; i < nx - 1; i++)
	{
		for (int j = 0; j < ny - 1; j++)
		{
			vx[i][j] = (psi[i][j + 1] - psi[i][j - 1]) / (2 * delta);
			vy[i][j] = (psi[i + 1][j] - psi[i - 1][j]) / (2 * delta);
		}
	}

	// wyznaczenie pola predkosci na zastawce
	for (int i = i1; i <= i2; i++)
		for (int j = 0; j <= j2; j++)
			vx[i][j] = vy[i][j] = 0;

	// na dolnym i gornym brzegu
	for (int i = 1; i < nx; i++)
		vx[i][0] = vy[i][ny] = 0;

	// na lewym i prawym brzegu przepisanie predkosci z sasiednich wezlow
	for (int j = 0; j <= ny; j++)
		vx[0][j] = vy[1][j];

	for (int j = 0; j <= ny; j++)
		vx[nx][j] = vy[nx - 1][j];

	// wyznaczenie vMac i deltaT

	{
		double maxModul = -1.0;
		double modul;
		for (int i = 0; i <= nx; i++)
		{
			for (int j = 0; j <= ny; j++)
			{
				modul = sqrt(pow(vx[i][j], 2) + pow(vy[i][j], 2));
				if (maxModul < modul)
					maxModul = modul;
			}
		}

		vMax = maxModul;
		deltaT = delta / (4 * vMax);
	}

	// inicjalizacja gestoci
	for (int i = 0; i <= nx; i++)
	{
		for (int j = 0; j <= ny; j++)
		{
			u0[i][j] = rozkladGestoci(delta * i, delta * j);
		}
	}

	for (int it = 1; it <= IT_MAX; it++)
	{
		// inicjalizacja kolejngeo kroku
		for (int i = 0; i <= nx; i++)
			for (int j = 0; j <= ny; j++)
				u1[i][j] = u0[i][j];

		for (int k = 1; k <= 20; k++)
		{
			for (int i = 0; i <= nx; i++)
			{
				for (int j = 1; j < ny; j++)
				{
					if ((i >= i1 && i <= i2) && (j <= j2))
						continue;
					else if (i == 0 || i == nx)
					{
						i = (i == 0 ? nx : 0);
						u1[i][j] = (1.0 / (1 + (2 * D * deltaT) / (pow(delta, 2)))) * (u0[i][j] -
																					   ((deltaT) / (2)) * vx[i][j] *
																					   (((u0[i + 1][j] - u0[i - 1][j]) /
																						 (2 * delta)) +
																						pow((u1[i + 1][j] -
																							 u1[i - 1][j]) /
																							(2 * delta), k))
																					   - ((deltaT) / (2)) * vy[i][j] *
																						 (((u0[i][j + 1] -
																							u0[i][j - 1]) /
																						   (2 * delta)) +
																						  pow((u1[i][j + 1] -
																							   u1[i][j - 1]) /
																							  (2 * delta), k))
																					   + ((deltaT) / (2)) * D *
																						 (((u0[i + 1][j] +
																							u0[i - 1][j] +
																							u0[i][j + 1] +
																							u0[i][j - 1] -
																							4 * u0[i][j]) /
																						   (pow(delta, 2))) +
																						  pow((u1[i + 1][j] +
																							   u1[i - 1][j] +
																							   u1[i][j + 1] +
																							   u1[i][j - 1]) /
																							  (pow(delta, 2)), k)));
					std::cout<<u1[i][j]<<std::endl;
					}
					else
					{
						u1[i][j] = (1.0 / (1 + (2 * D * deltaT) / (pow(delta, 2)))) * (u0[i][j] -
																					   ((deltaT) / (2)) * vx[i][j] *
																					   (((u0[i + 1][j] - u0[i - 1][j]) /
																						 (2 * delta)) +
																						pow((u1[i + 1][j] -
																							 u1[i - 1][j]) /
																							(2 * delta), k))
																					   - ((deltaT) / (2)) * vy[i][j] *
																						 (((u0[i][j + 1] -
																							u0[i][j - 1]) /
																						   (2 * delta)) +
																						  pow((u1[i][j + 1] -
																							   u1[i][j - 1]) /
																							  (2 * delta), k))
																					   + ((deltaT) / (2)) * D *
																						 (((u0[i + 1][j] +
																							u0[i - 1][j] +
																							u0[i][j + 1] +
																							u0[i][j - 1] -
																							4 * u0[i][j]) /
																						   (pow(delta, 2))) +
																						  pow((u1[i + 1][j] +
																							   u1[i - 1][j] +
																							   u1[i][j + 1] +
																							   u1[i][j - 1]) /
																							  (pow(delta, 2)), k)));
						std::cout<<u1[i][j]<<std::endl;
					}
				}
			}
		}

		for (int i = 0; i <= nx; i++)
			for (int j = 0; j <= ny; j++)
				u0[i][j] = u1[i][j];

		double c = 0;
		double xsr = 0;
		for (int i = 0; i <= nx; i++)
		{
			for (int j = 0; j <= ny; j++)
			{
				c += u0[i][j];
				c *= pow(delta, 2);
				xsr += i * delta * u0[i][j];
				xsr *= pow(delta, 2);
			}
		}

		calka << it << " " << c << std::endl;
		sredniePolozeniePakietu << it << " " << xsr << std::endl;

	}

}

double rozkladGestoci(double x, double y)
{
	double value = (1.0 / (2 * M_PI * pow(sigma, 2))) * exp(-(pow(x - xA, 2) + pow(y - yA, 2)) / (2 * pow(sigma, 2)));
}


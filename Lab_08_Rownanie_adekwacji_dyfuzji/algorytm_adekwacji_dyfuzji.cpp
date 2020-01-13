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

	std::fstream inputFile;
	std::fstream calka;
	std::fstream sredniePolozeniePakietu;
	std::fstream mapaRozkladu;
	std::fstream test;

	inputFile.open("psi.dat");
	calka.open("calka_D=" + std::to_string(D) + "IT_MAX=" + std::to_string(IT_MAX) + ".dat", std::ios::out);
	sredniePolozeniePakietu.open("xsr_D=" + std::to_string(D) + "IT_MAX=" + std::to_string(IT_MAX) + ".dat", std::ios::out);
	mapaRozkladu.open("mapa_D=" + std::to_string(D) + "IT_MAX=" + std::to_string(IT_MAX) + ".dat", std::ios::out);
	test.open("test.dat", std::ios::out);

	if (inputFile.fail())
	{
		std::cout << "not ok";
		return;
	}

	// wczytanie funkcji strumienia
	{
		int a, b;
		for (int i = 0; i <= nx; i++)
			for (int j = 0; j <= ny; j++)
				inputFile >> a >> b >> psi[i][j];
	}

	// wyznaczenie pola predkosci
	for (int i = 1; i < nx; i++)
	{
		for (int j = 1; j < ny; j++)
		{
			vx[i][j] = (psi[i][j + 1] - psi[i][j - 1]) / (2 * delta);
			vy[i][j] = -(psi[i + 1][j] - psi[i - 1][j]) / (2 * delta);
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
		vx[0][j] = vx[1][j];

	for (int j = 0; j <= ny; j++)
		vx[nx][j] = vx[nx - 1][j];


	for (int i=0;i<=nx;i++) {
		for (int j=0;j<=ny;j++) 
			test << i << " " << j << " " << vx[i][j] << " " << vy[i][j] <<std::endl;
			test << std::endl;
	}

	// wyznaczenie vMax i deltaT

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
		std::cout<<deltaT<<std::endl;
	}

	// inicjalizacja gestoci
	for (int i = 0; i <= nx; i++)
	{
		for (int j = 0; j <= ny; j++)
		{
			u0[i][j] = rozkladGestoci(delta * i, delta * j);
			// std::cout<<u0[i][j]<<std::endl
			;
		}
	}

	// for (int i=0;i<=nx;i++) {
	// 	for (int j=0;j<=ny;j++)
	// 		test << u0[i][j] <<std::endl;
	// }


	for (int it = 1; it <= IT_MAX; it++)
	{
		// inicjalizacja kolejngeo kroku
		for (int i = 0; i <= nx; i++)
			for (int j = 0; j <= ny; j++) {
				u1[i][j] = u0[i][j];
			}

		for (int k = 1; k <= 20; k++)
		{
			for (int j = 1; j < ny; j++)
			{
				for (int i = 0; i <= nx; i++)
				{

					int im1, ip1;
					if (i==0) {
						im1 = nx;
						ip1 = i+1;
					} else if (i == nx) {
						im1 = i-1;
						ip1 = 0;
					} else {
						im1 = i-1;
						ip1 = i+1;
					}
						
					if ((i >= i1 && i <= i2) && (j <= j2))
						continue;

					u1[i][j] = (1.0/(1 + (2*D * deltaT)/(pow(delta,2)))) * (u0[i][j] 
					-(deltaT/2.0) * vx[i][j] * (u0[ip1][j] - u0[im1][j] + u1[ip1][j] - u1[im1][j])/2/delta
					- deltaT/2 * vy[i][j] * (u0[i][j+1] - u0[i][j-1] + u1[i][j+1] - u1[i][j-1])/2/delta
					+ deltaT/2 * D*(u0[ip1][j] + u0[im1][j] + u0[i][j+1] + u0[i][j-1] - 4*u0[i][j] + u1[ip1][j] + u1[im1][j] + u1[i][j+1] + u1[i][j-1])/delta/delta
					);
				}
			}
				
		}
		for (int i = 0; i <= nx; i++)
			for (int j = 0; j <= ny; j++)
				u0[i][j] = u1[i][j];



		// 	for (int i=0;i<=nx;i++) {
		// for (int j=0;j<=ny;j++)
		// 	test << i << " " << j << " " << u1[i][j] << std::endl;

		double c = 0;
		double xsr = 0;
		for (int i = 0; i <= nx; i++)
		{
			for (int j = 0; j <= ny; j++)
			{
				c += u0[i][j];
				xsr += i * delta * u0[i][j];
			}
		}

		c *= pow(delta, 2);
		xsr *= pow(delta, 2);


		calka << it * deltaT << " " << c << std::endl;
		sredniePolozeniePakietu << it * deltaT << " " << xsr << std::endl;
		std::cout<< "nr it: " << it  << " calka: " << c<<std::endl;
		std::cout<<"xsr: " << xsr <<std::endl;
	
	}

		for (int i=0;i<=nx;i++) {
			for (int j=0;j<=ny;j++) {
				mapaRozkladu << i << " " << j << " " << " " <<u1[i][j] <<std::endl;
			}
			mapaRozkladu << std::endl;
		}


	}



double rozkladGestoci(double x, double y)
{
	// std::cout<<x << " " << y <<std::endl;
	double value = (1.0 / (2 * M_PI * pow(sigma, 2))) * exp(-(pow(x - xA, 2) + pow(y - yA, 2)) / (2 * pow(sigma, 2)));
	// std::cout<<value<<std::endl;
	return value;
}


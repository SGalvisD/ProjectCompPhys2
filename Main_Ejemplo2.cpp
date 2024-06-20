#include<vector>
#include<functional>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include"Poisson.h"

using namespace std;


int main() {
    //double x, y;

    double a = -4, b = 4.0, c = -4.0, d = 4.0; // Límites del dominio
    int m = 10, n = 10; // Número de puntos en cada dirección
    double Tol = 1e-6; // Tolerancia
    int N = 1000; // Número máximo de iteraciones

    double M = 1.0; // Masa de la galaxia
    double alpha = 0.1; // Radio característico de la galaxia



    auto f = [alpha,M](double x, double y) { 
        double ratio = (pow(x,2)+pow(y,2))/pow(alpha,2);
        return M/(2*M_PI*pow(alpha,2))*pow((1+ratio),-1.5);
        };
    auto g = [](double x, double y) { return 0.0; };

    PoissonSolver solver(a, b, c, d, m, n, Tol, N, f, g);
    solver.solve();
    solver.guardarcvs("Solucion_Ejemplo2.csv");
    

    return 0;    
}
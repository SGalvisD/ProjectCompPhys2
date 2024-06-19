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

    double a = 0.0, b = 2.0, c = 0.0, d = 1.0; // Límites del dominio
    int m = 5, n = 6; // Número de puntos en cada dirección
    double Tol = 1e-6; // Tolerancia
    int N = 100; // Número máximo de iteraciones

    double M = 1.0; // Masa de la galaxia



    auto f = [a,M](double x, double y) { 
        double ratio = (pow(x,2)+pow(y,2))/pow(a,2);
        return M/(2*M_PI*pow(a,2))*pow((1+ratio),-1.5);
        };
    auto g = [](double x, double y) { return 0.0; };

    PoissonSolver solver(a, b, c, d, m, n, Tol, N, f, g);
    solver.solve();
    solver.guardarcvs("Solucion_Ejemplo2.csv");
    

    return 0;    
}
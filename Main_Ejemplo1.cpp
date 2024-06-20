#include<vector>
#include<functional>
#include<iostream>
#include<fstream>
#include<string>
#include"Poisson.h"

using namespace std;


int main() {
    //double x, y;

    double a = 0.0, b = 2.0, c = 0.0, d = 1.0; // Límites del dominio
    int m = 7, n = 4; // Número de puntos en cada dirección
    double Tol = 1e-9; // Tolerancia
    int N = 1000; // Número máximo de iteraciones
    
    double V_0 = 1.0; // Valor de V en y = d

    auto f = [](double x, double y) { return 0.0; };
    auto g = [a,b,c,d,V_0](double x, double y) {
        if (y == d) {
            return V_0;
    }
        else {
            return 0.0;
        }
    };

    PoissonSolver solver(a, b, c, d, m, n, Tol, N, f, g);
    solver.solve();
    solver.guardarcvs("Solucion_Ejemplo1.csv");
    

    return 0;    
}
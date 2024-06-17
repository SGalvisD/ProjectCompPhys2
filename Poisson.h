#include<vector>
#include<functional>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class PoissonSolver {
private:
    // Límites de la región
    double a, b, c, d;

    // Número de puntos en X y en Y
    int m, n;

    // Tolerancia
    double Tol;

    // Número de iteraciones
    int N;

    // Parámetros de la malla
    double h, k;

    // Parámetros de la ecuación
    double lam, mu;

    // Vectores y matriz de la solución
    vector<double> x;
    vector<double> y;
    vector<vector<double>> w;

    // Funciones de la ecuación
    function<double(double, double)> f;
    function<double(double, double)> g;

    string filename;

public:
    // Constructor
    PoissonSolver(double a, double b, double c, double d, int m, int n, double Tol, int N,function<double(double, double)> f, function<double(double, double)> g);

    // Método para resolver la ecuación 
    void solve();

    // Método para guardar la solución en un archivo .csv (Opcional)
    void guardarcvs(string);
};
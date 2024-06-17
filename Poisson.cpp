#include<vector>
#include<functional>
#include<iostream>
#include<fstream>
#include<string>
#include"Poisson.h"

using namespace std;

PoissonSolver :: PoissonSolver(double a, double b, double c, double d, int m, int n, double Tol, int N,function<double(double, double)> f, function<double(double, double)> g):
a(a), b(b), c(c), d(d), m(m), n(n), Tol(Tol), N(N), f(f),g(g) {
    
    // Inicializar los parámetros de la malla
    h = (b - a) / n;
    k = (d - c) / m;
    lam = (h * h) / (k * k);
    mu = 2 * (1 + lam);
    
    // Inicializar los vectores y la matriz de la solución
    x.resize(n);
    y.resize(m);
    w.resize(n, vector<double>(m, 0.0));

    // Inicializar los valores de X y Y
    for (int i = 1; i <= n-1; i++) {
        x[i] = a + i * h;
        for (int j = 1; j <= m-1; j++) {
            y[j] = c + j * k;
            w[i][j] = 0.0;
        }
    }
}

void PoissonSolver :: solve() {
    int l = 1;
    double norm;
    double z;

    while (l <= N) {

        // Calculando el Z y Norma inicial
        z = (-h*h*f(x[1],y[m-1])+g(a,y[m-1])+lam*g(x[1],d)+lam*w[1][m-2]+w[2][m-1])/mu;
        norm = abs(z-w[1][m-1]);
        w[1][m-1]=z; // Actualizando el valor de w inicial

        // Calculando el valor de w en la frontera de arriba
        for (int i = 2; i <= n-2; i++) {

            z = (-h * h * f(x[i], y[m-1]) + lam*g(x[i], d) + w[i - 1][m-1] + w[i + 1][m-1] + lam*w[i][m-2]) / mu;
            if (abs(w[i][m-1] - z) > norm) {
                    norm = abs(w[i][m-1] - z);
                }
            w[i][m-1] = z;
            
        }
        
        // Calculando el valor de w en la frontera de arriba derecha

        z= (-h*h*f(x[n-1],y[m-1])+g(b,y[m-1])+lam*g(x[n-1],d)+w[n-2][m-1]+lam*w[n-1][m-2])/mu;

        if (abs(w[n-1][m-1]-z)>norm){
            norm=abs(w[n-1][m-1]-z);

        }
        
        w[n-1][m-1]=z;
        
        for(int j=m-2; j>=2;j--){
            z = (-h*h*f(x[1],y[j])+g(a,y[j])+lam*w[1][j+1]+lam*w[1][j-1]+w[2][j])/mu;
            if(abs(w[1][j]-z)>norm){
                norm=abs(w[1][j]-z);
            }
            w[1][j]=z;

            for(int i=2; i<=n-2;i++){
                z= (-h*h*f(x[i],y[j])+w[i-1][j]+lam*w[i][j+1]+w[i+1][j]+lam*w[i][j-1])/mu;
                if(abs(w[i][j]-z)>norm){
                    norm=abs(w[i][j]-z);
                }
                w[i][j]=z;
            }
            z= (-h*h*f(x[n-1],y[j])+g(b,y[j])+w[n-2][j]+lam*w[n-1][j+1]+lam*w[n-1][j-1])/mu;
            if(abs(w[n-1][j]-z)>norm){
                norm=abs(w[n-1][j]-z);

            }
            w[n-1][j]=z;

        }

        // Calculando el valor de w en la frontera de abajo izquierda
        z= (-h*h*f(x[1],y[1])+g(a,y[1])+lam*g(x[1],c)+lam*w[1][2]+w[2][1])/mu;
        if(abs(w[1][1]-z)>norm){
            norm= w[1][1]-z;
        }

        w[1][1]=z;

        for(int i=2;i<=n-2;i++){
            z= (-h*h*f(x[i],y[1])+lam*g(x[i],c)+w[i-1][1]+lam*w[i][2]+w[i+1][1])/mu;
            if(abs(w[i][1]-z)>norm){
                norm=abs(w[i][1]-z);

            }
            w[i][1]=z;
        }

        z= (-h*h*f(x[n-1],y[1])+g(b,y[1])+lam*g(x[n-1],c)+w[n-2][1]+lam*w[n-1][2])/mu;
        if(abs(w[n-1][1]-z)>norm){
            norm=abs(w[n-1][1]-z);
        }
        w[n-1][1]=z;





        if (norm < Tol) {
            cout << "La solución converge luego de " << l << " iteraciones." << endl;
            break;
        }

        l++;
    }

    if (l > N) {
        cout << "La solución no converge." << endl;
    }
}


void PoissonSolver :: guardarcvs(string filename){

    ofstream file(filename);
    if (file.is_open()) {
        // Escribir los encabezados
        file << "x,y,Wij,Uij,Dif\n";

        // Escribir los datos
        for (int i = 1; i <= n - 1; i++) {
            for (int j = 1; j <= m - 1; j++) {
                file << x[i] <<","<< y[j] <<","<< w[i][j] << "," << f(x[i],y[j]) <<","<<abs(w[i][j]-f(x[i],y[j]))<< "\n";
            }
        }

        file.close();
        cout << "Los datos se han guardado en el archivo "<<filename << endl;
    } else {
        cout << "No se pudo abrir el archivo data.csv." << endl;
    }


}
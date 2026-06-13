#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cmath>

#include "../arbolitos/AVL.h"
#include "../arbolitos/SplayTree.h"
#include "../RandomGen/RandomArray.h" 

using namespace std;
using namespace chrono;


class HPTimer {
private:
    high_resolution_clock::time_point startTime;

public:
    void start() {
        startTime = high_resolution_clock::now();
    }

    unsigned long long end() {
        auto endTime = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(endTime - startTime);
        return duration.count();
    }
};

void experimentar(string& tipo, 
                  BTree* arbol, 
                  string& nombre, 
                  vector<uint>& datosInsercion, 
                  vector<uint>& datosBusqueda, 
                  int N, 
                  int M, 
                  ofstream& csv) {

    HPTimer timer;

    for (uint val : datosInsercion) {
        arbol->insert(val);
    }
    unsigned long long tiempoIns = timer.end();

    csv << N << "," << tipo << "," << nombre << ",InsercionTotal," << tiempoIns << "\n";
    
    for (int i = 0; i < M; ++i) {
        uint val = datosBusqueda[i];
        
        timer.start();
        arbol->search(val);
        unsigned long long tiempoBsq = timer.end();
        
        csv << N << "," << tipo << "," << nombre << ",Busqueda_" << i << "," << tiempoBsq << "\n";
    }
}                    


int main() {
    ofstream csv("resultados.csv");
    csv << "N,Tipo,Nombre,Operacion,Tiempo(ns)\n";

    int c = 2;

    for (int exp = 10; exp <= 14; ++exp) {
        size_t N = 1ULL << exp;
        size_t M = 10 * c * N;

        cout << "N = " << N << "  M = " << M << " ..." << flush;

        RandomValues generador(N);

        vector<uint> insercionAleatoria = generador.getVal(N);

        vector<uint> insercionOrdenada = insercionAleatoria;
        sort(insercionOrdenada.begin(), insercionOrdenada.end());

        vector<uint> busquedaUniforme(M);
        for (size_t i = 0; i < M; ++i) {
            uint idxAleatorio = static_cast<uint>(rand() % N);
            busquedaUniforme[i] = generador[idxAleatorio];
        }

        vector<uint> busquedaSesgada = generador.getVal(M);

        {
            AVL avl;
            SplayTree splay;
            experimentar("a", &avl,   "AVL",   insercionAleatoria, busquedaUniforme, N, M, csv);
            experimentar("a", &splay, "Splay", insercionAleatoria, busquedaUniforme, N, M, csv);
        }

        {
            AVL avl;
            SplayTree splay;
            experimentar("b", &avl,   "AVL",   insercionAleatoria, busquedaSesgada, N, M, csv);
            experimentar("b", &splay, "Splay", insercionAleatoria, busquedaSesgada, N, M, csv);
        }

        {
            AVL avl;
            SplayTree splay;
            experimentar("c", &avl,   "AVL",   insercionOrdenada, busquedaUniforme, N, M, csv);
            experimentar("c", &splay, "Splay", insercionOrdenada, busquedaUniforme, N, M, csv);
        }

        {
            AVL avl;
            SplayTree splay;
            experimentar("d", &avl,   "AVL",   insercionOrdenada, busquedaSesgada, N, M, csv);
            experimentar("d", &splay, "Splay", insercionOrdenada, busquedaSesgada, N, M, csv);
        }

        cout << " OK" << endl;
    }

    csv.close();
    cout << "Resultados guardados en resultados.csv" << endl;
    return 0;
}

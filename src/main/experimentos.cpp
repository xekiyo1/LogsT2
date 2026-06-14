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
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
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

void experimentar(const string &tipo,
                  BTree* arbol,
                  const string &nombre,
                  const vector<uint>& datosInsercion,
                  const vector<uint>& datosBusqueda,
                  const std::size_t N,
                  const std::size_t M,
                  ofstream& csv) {

    HPTimer timer;

    for (const uint val : datosInsercion)
        arbol->insert(val);

    unsigned long long tiempoIns = timer.end();

    csv << N << "," << tipo << "," << nombre << ",InsercionTotal," << tiempoIns << "\n";
    
    for (int i = 0; i < M; ++i) {
        const uint val = datosBusqueda[i];
        
        timer.start();
        arbol->search(val);
        const unsigned long long tiempoBsq = timer.end();
        
        csv << N << "," << tipo << "," << nombre << ",Busqueda_" << i << "," << tiempoBsq << "\n";
    }
}                    

void experimentarAmbos(const string &etiquetaExperimento,
                    const vector<uint>& datosInsercion,
                    const vector<uint>& datosBusqueda,
                    const std::size_t N,
                    const std::size_t M,
                    ofstream& csv) {
    AVL avl;
    SplayTree splay;
    experimentar("b", &avl,   "AVL",   datosInsercion, datosBusqueda, N, M, csv);
    experimentar("b", &splay, "Splay", datosInsercion, datosBusqueda, N, M, csv);
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

        experimentarAmbos("a", insercionAleatoria, busquedaUniforme, N, M, csv);
        experimentarAmbos("b", insercionAleatoria, busquedaSesgada, N, M, csv);
        experimentarAmbos("c", insercionOrdenada, busquedaUniforme, N, M, csv);
        experimentarAmbos("d", insercionOrdenada, busquedaSesgada, N, M, csv);

        cout << " OK" << endl;
    }

    csv.close();
    cout << "Resultados guardados en resultados.csv" << endl;
    return 0;
}

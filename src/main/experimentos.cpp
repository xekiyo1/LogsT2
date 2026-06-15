#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <cmath>

#include "../arbolitos/BinaryTree.h"
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
        cout<<"iniciando..."<<endl;
        csv << N << "," << tipo << "," << nombre << ",Busqueda_" << i << "," << tiempoBsq << "\n";
    }
}                    

void experimentarAmbos(const string &etiquetaExperimento,
                    const vector<uint>& datosInsercion,
                    const vector<uint>& datosBusqueda,
                    const std::size_t N,
                    const std::size_t M,
                    ofstream& csv) {
    BTree* arbol = new SplayTree;
    experimentar(etiquetaExperimento, arbol, "Splay", datosInsercion, datosBusqueda, N, M, csv);
    delete arbol;
    /*
    arbol = new AVL;
    experimentar(etiquetaExperimento, arbol,   "AVL",   datosInsercion, datosBusqueda, N, M, csv);
    delete arbol;*/
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
        string label = "a";
        for (uint i=0;i<2;i++) {
            // experimento de insercion y busqueda aleatoria
            cout << "Inserción aleatoria con búsqueda" << (i?"sesgada":"uniforme") << endl;
            vector<uint> insercion = generador.getVal(N); //por defecto es uniforme
            vector<uint> busqueda = generador.getVal(M, i); //la primera vez uniforme, la segunda sesgada
            experimentarAmbos(label, insercion, busqueda, N, M, csv);

            label[0] += 1;

            //ahora insertando de forma ordenada
            cout << "Inserción ordenada con búsqueda" << (i?"sesgada":"uniforme") << endl;
            insercion = generador.getVal(N);
            busqueda = generador.getVal(M,i);//la primera vez uniforme, la segunda sesgada

            sort(insercion.begin(),insercion.end());
            experimentarAmbos(label, insercion, busqueda, N, M, csv);
            label[0] += 1;
        }

        cout << " OK" << endl;
    }

    csv.close();
    cout << "Resultados guardados en resultados.csv" << endl;
    return 0;
}

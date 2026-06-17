#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <random>

#include "../arbolitos/BinaryTree.h"
#include "../arbolitos/AVL.h"
#include "../arbolitos/SplayTree.h"
#include "../RandomGen/RandomArray.h" 
#include "HPTimer.cpp"

void experimentar(const string &tipo,
                  BTree* arbol,
                  const string &nombre,
                  const vector<uint>& datosInsercion,
                  const vector<uint>& datosBusqueda,
                  const std::size_t N,
                  const std::size_t M,
                  ofstream& csv) {

    HPTimer timer;

    timer.start();
    for (const uint val : datosInsercion)
        arbol->insert(val);
    unsigned long long tiempoIns = timer.end();
    csv << N << "," << tipo << "," << nombre << ",InsercionTotal," << tiempoIns << "\n";

    timer.start();
    for (int i = 0; i < M; ++i)
        arbol->search(datosBusqueda[i]);
    const unsigned long long tiempoBsq = timer.end();
    csv << N << "," << tipo << "," << nombre << ",busqueda," << tiempoBsq << "\n";
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

    arbol = new AVL;
    experimentar(etiquetaExperimento, arbol,   "AVL",   datosInsercion, datosBusqueda, N, M, csv);
    delete arbol;
}

int main() {
    ofstream csv("resultados.csv");
    csv << "N,Tipo,Nombre,Operacion,Tiempo(ns)\n";

    int c = 2;

    for (int exp = 10; exp <= 14; ++exp) {
        size_t N = 1ULL << exp;
        size_t M = 10 * c * N;

        cout << "N = " << N << "  M = " << M << " ..." << endl;

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
    cout << "Resultados guardados en resultados.csv" << endl;

    csv.close();
    return 0;
}

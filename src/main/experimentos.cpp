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

/**
 * Realiza un experimento de inserción y búsqueda en un árbol, y guarda
 * los resultados de tiempo para cada acción en un archivo csv.
 * @param tipo Etiqueta del experimento que se escribirá al archivo.
 * @param arbol Árbol que se utilizará para la inserción y búsqueda.
 * @param nombre Nombre del tipo de árbol (AVL o SplayTree)
 * @param datosInsercion Valores que se insertarán en los árboles.
 * @param datosBusqueda Valores que se buscarán en los árboles una vez construidos.
 * @param N Cantidad de valores a insertar.
 * @param M Cantidad de valores a buscar
 * @param csv Archivo al que se guardarán los resultados.
 */
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

/**
 * Realiza un experimento de inserción y búsqueda en ambos tipos de árbol, y guarda
 * los resultados en un archivo csv.
 * @param etiquetaExperimento Identificador del experimento, que se usará para el archivo.
 * @param datosInsercion Valores que se insertarán en los árboles.
 * @param datosBusqueda Valores que se buscarán en los árboles una vez construidos.
 * @param N Cantidad de valores a insertar.
 * @param M Cantidad de valores a buscar
 * @param csv Archivo al que se guardarán los resultados.
 */
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

/// Vector de etiquetas con propósito de impresión.
std::vector<string> labels = {
    "Aleatorio uniforme",
    "Ordenado Uniforme",
    "Aleatorio sesgado",
    "Ordenado sesgado"
};
/// Índice del nombre del experimento en realización.
uint label_idx = 0;

int main() {
    ofstream csv("resultados.csv");
    csv << "N,Tipo,Nombre,Operacion,Tiempo(ns)\n";

    for (int exp = 10; exp <= 14; ++exp) {
        size_t N = 1ULL << exp;
        size_t M = 10 * c * N;

        cout << "N = " << N << "  M = " << M << " ..." << endl;

        RandomValues generador(N);
        label_idx = 0;
        for (uint i=0;i<2;i++) {
            // experimento de insercion y busqueda aleatoria
            cout << "Inserción aleatoria con búsqueda" << (i?"sesgada":"uniforme") << endl;
            vector<uint> insercion = generador.getVal(N); //por defecto es uniforme
            vector<uint> busqueda = generador.getVal(M, i); //la primera vez uniforme, la segunda sesgada
            experimentarAmbos(labels[label_idx], insercion, busqueda, N, M, csv);

            label_idx++;

            //ahora insertando de forma ordenada
            cout << "Inserción ordenada con búsqueda" << (i?"sesgada":"uniforme") << endl;
            insercion = generador.getVal(N);
            busqueda = generador.getVal(M,i);//la primera vez uniforme, la segunda sesgada

            sort(insercion.begin(),insercion.end());
            experimentarAmbos(labels[label_idx], insercion, busqueda, N, M, csv);
            label_idx++;
        }

        cout << " OK" << endl;
    }
    cout << "Resultados guardados en resultados.csv" << endl;

    csv.close();
    return 0;
}

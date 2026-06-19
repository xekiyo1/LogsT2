#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include "../arbolitos/BinaryTree.h"
#include "../arbolitos/AVL.h"
#include "../arbolitos/SplayTree.h"
#include "../RandomGen/RandomArray.h"
#include "HPTimer.cpp"

using namespace std;


void inorden(Nodo* raiz, vector<uint>* serie) {
    if (raiz != nullptr){
        inorden(raiz->izq,serie);
        serie->push_back(raiz->value);
        inorden(raiz->der,serie);
    }
} 


int main() {
    ofstream csv("teoremas.csv");

    size_t N = 1ULL << 25; // N = 2^25
    cout << "Hora de la experimentacion Bonus :v | N = " << N << endl;

    int semilla = 67; // semilla para reproducibilidad
    int semilla_permutacion = 69; // semilla para permutar
    mt19937_64 permutacion(69);

    RandomValues dataset(N,semilla);
    vector<uint> permutado = dataset.dataset;
    shuffle(permutado.begin(),permutado.end(), permutacion);

    cout << "Construyendo T1 y T2 (Se demora harto confíen otra vez)" << "\n" << flush;
    BTree* T1 = new SplayTree();
    BTree* T2 = new SplayTree();
    Nodo* nodo;
    for(size_t i = 0; i < N; ++i) {
        nodo = T1->insert(dataset[i]);
        T2->insert(permutado[i]);
    }

    vector<uint> serie;

    inorden(nodo,&serie);

    cout << "Recorriendo el arbol 2 con la serie"<< "\n" << flush;
    HPTimer timer;
    int numero = 1;
    for (uint i : serie){
        timer.start();
        T1->search(i);
        unsigned long long BonusTime = timer.end();
        csv << numero << ",Bonus,Splay,m=0," << BonusTime << "\n";
        numero++;
}

    cout << " LISTO." << endl;

    

}
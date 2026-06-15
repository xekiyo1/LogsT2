#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

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

void experimentarTeoremas(int c, ofstream& csv) {
    size_t N = 1ULL << 25; // N = 2^25
    cout << "Hora de la experimentacion :v" << N << endl;

    int semilla = 67; // semilla para reproducibilidad
    vector<uint> dataset(N);
    mt19937_64 rng(semilla); 
    uniform_int_distribution<uint> dist(0, 4294967295U);
    for (size_t i = 0; i < N; ++i) {
        dataset[i] = dist(rng);
    }

    cout << "Construyendo AVL y Splay Tree (Se demora harto confíen)" << flush;
    BTree* avl = new AVL();
    BTree* splay = new SplayTree();

    for(size_t i = 0; i < N; ++i) {
        avl->insert(dataset[i]);
        splay->insert(dataset[i]);
    }
    cout << " LISTO." << endl;

    vector<uint> dataset_sorted = dataset;
    sort(dataset_sorted.begin(), dataset_sorted.end());
    // eliminamos duplicados por orden estrictamente creciente
    dataset_sorted.erase(unique(dataset_sorted.begin(), dataset_sorted.end()), dataset_sorted.end());
    size_t N_unique = dataset_sorted.size();

    cout << "\nSequential Access Theorem" << endl;
    for(int i = 1; i <= 10; ++i) {
        size_t m = (N * i) / 100;
        cout << "  m = " << m << " (" << i << "N/100)... " << flush;

        // usamos m elementos crecientes equiespaciados pq es más facil
        vector<uint> seq_access;
        seq_access.reserve(m);
        size_t step = N_unique / m;
        for(size_t j = 0; j < m; ++j) {
            seq_access.push_back(dataset_sorted[j * step]);
        }

        HPTimer timer;

        // Test AVL
        timer.start();
        for(uint key : seq_access) avl->search(key);
        unsigned long long timeAVL = timer.end();
        csv << N << ",SeqAccess,AVL,m=" << m << "," << timeAVL << "\n";

        // Test Splay
        timer.start();
        for(uint key : seq_access) splay->search(key);
        unsigned long long timeSplay = timer.end();
        csv << N << ",SeqAccess,Splay,m=" << m << "," << timeSplay << "\n";

        cout << "OK" << endl;
    }

    // Working Set Theorem
    cout << "\nWorking Set Theorem" << endl;
    size_t M = 10ULL * c * N; 
    vector<size_t> W_values = {10, 100, 1000, 10000, 100000, 1000000};

    for(size_t W : W_values) {
        cout << "  W = " << W << "... " << flush;

        // elegir W elementos aleatorios (subset W)
        vector<uint> working_set;
        working_set.reserve(W);
        uniform_int_distribution<size_t> distIdx(0, N - 1);
        for(size_t j = 0; j < W; ++j) {
            working_set.push_back(dataset[distIdx(rng)]);
        }

        
        //Indices Random Precalculados (Calculo 5 millones pq tener N^25 sería muy insano lowkey highkey no cap on god bro)
        size_t blockSize = min(M, (size_t)5000000); 
        vector<uint> rnd_idx(blockSize);
        uniform_int_distribution<size_t> wsDist(0, W - 1);
        for(size_t j = 0; j < blockSize; ++j) {
            rnd_idx[j] = working_set[wsDist(rng)];
        }

        HPTimer timer;

        // Test AVL
        timer.start();
        for(size_t k = 0; k < M; ++k) {
            avl->search(rnd_idx[k % blockSize]); 
        }
        unsigned long long timeAVL_WS = timer.end();
        csv << N << ",WorkingSet,AVL,W=" << W << "," << timeAVL_WS << "\n";

        // Test Splay
        timer.start();
        for(size_t k = 0; k < M; ++k) {
            splay->search(rnd_idx[k % blockSize]);
        }
        unsigned long long timeSplay_WS = timer.end();
        csv << N << ",WorkingSet,Splay,W=" << W << "," << timeSplay_WS << "\n";

        cout << "OK" << endl;
    }

    delete avl;
    delete splay;

    cout << "La experimentación ha sido completada y somos sigmas" << endl;

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

    experimentarTeoremas(c, csv);


    csv.close();
    return 0;
}

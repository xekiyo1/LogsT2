#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include "../arbolitos/BinaryTree.h"
#include "../arbolitos/AVL.h"
#include "../arbolitos/SplayTree.h"
#include "HPTimer.cpp"

int main() {
    int c = 2;
    ofstream csv("teoremas.csv");

    size_t N = 1ULL << 25; // N = 2^25
    cout << "Hora de la experimentacion :v" << N << endl;

    int semilla = 67; // semilla para reproducibilidad
    vector<uint> dataset(N);
    mt19937_64 rng(semilla);
    uniform_int_distribution<uint> dist(0, 4294967295U);
    for (size_t i = 0; i < N; ++i)
        dataset[i] = dist(rng);

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
    dataset_sorted.clear();

    // Working Set Theorem
    cout << "\nWorking Set Theorem" << endl;
    size_t M = 10ULL * c * N;
    vector<size_t> W_values = {10, 100, 1000, 10000, 100000, 1000000};
    vector<uint> working_set;
    for(size_t W : W_values) {
        cout << "  W = " << W << "... " << flush;

        // elegir W elementos aleatorios (subset W)
        working_set.resize(W);
        uniform_int_distribution<size_t> distIdx(0, N - 1);
        for(uint &j : working_set)
            j = dataset[distIdx(rng)];


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
        for(size_t k = 0; k < M; ++k)
            avl->search(rnd_idx[k % blockSize]);
        unsigned long long timeAVL_WS = timer.end();
        csv << N << ",WorkingSet,AVL,W=" << W << "," << timeAVL_WS << "\n";

        // Test Splay
        timer.start();
        for(size_t k = 0; k < M; ++k)
            splay->search(rnd_idx[k % blockSize]);
        unsigned long long timeSplay_WS = timer.end();
        csv << N << ",WorkingSet,Splay,W=" << W << "," << timeSplay_WS << "\n";

        cout << "OK" << endl;
    }

    delete avl;
    delete splay;

    csv.close();
    cout << "La experimentación ha sido completada y somos sigmas" << endl;
    return 0;
}
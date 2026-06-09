//
// Created by elnchou on 08-06-26.
//

#include "BinaryTree.h"
#include <queue>

Nodo *BTree::search(const uint val) {
    Nodo* ans = raiz;
    while (ans != nullptr && ans->value != val)
        raiz = raiz->value < val ? raiz->izq : raiz->der;
    return ans;
}

void BTree::clear(const bool deleteObj) {
    std::queue<Nodo*> bfs = {raiz};
    while (!bfs.empty()) {
        raiz = bfs.front(); bfs.pop();
        if (raiz->der != nullptr) bfs.push(raiz->der);
        if (raiz->izq != nullptr) bfs.push(raiz->izq);
        if (deleteObj) delete raiz;
    }
    raiz = nullptr;
}

//probablemente nunca lo usemos pero para tenerlo
void BTree::insert(const uint val) {
    if (raiz==nullptr) {
        raiz = new Nodo{val,nullptr,nullptr};
        return;
    }

    Nodo *parent = raiz;

    for (;;) {
        if (val == parent->value) return;
        if (val < parent->value) {
            if (parent->izq == nullptr) {
                parent->izq = new Nodo{val,nullptr,nullptr};
                return;
            }
            parent = parent->izq;
        }else {
            if (parent->der == nullptr) {
                parent->der = new Nodo{val,nullptr,nullptr};
                return;
            }
            parent = parent->der;
        }
    }
}

BTree::~BTree() {
    clear();
}

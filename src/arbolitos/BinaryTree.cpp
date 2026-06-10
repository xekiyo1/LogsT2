//
// Created by elnchou on 08-06-26.
//

#include "BinaryTree.h"
#include <queue>
#include <algorithm>

void BTree::zag(Nodo *nodo) {
    Nodo *obj = nodo->izq;

    // cambiar los padres
    obj->parent = nodo->parent;
    nodo->parent = obj;

    // cambiar las aristas
    std::swap(nodo->izq, obj->der);

    //actualizar altura
    nodo->height--; obj->height++;
}

void BTree::zig(Nodo *nodo) {
    Nodo *obj = nodo->der;

    // cambiar los padres
    obj->parent = nodo->parent;
    nodo->parent = obj;

    // cambiar las aristas y altura
    std::swap(nodo->der, obj->izq);
    //actualizar altura
    nodo->height--; obj->height++;
}

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
Nodo* BTree::insert(const uint val) {
    if (raiz==nullptr) {
        raiz = new Nodo{val,nullptr,nullptr};
        return raiz;
    }

    Nodo *parent = raiz;

    for (;;) {
        if (val == parent->value) return parent;
        if (val < parent->value) {
            if (parent->izq == nullptr) {
                parent->izq = new Nodo{val,nullptr,nullptr};
                return parent->izq;
            }
            parent = parent->izq;
        }else {
            if (parent->der == nullptr) {
                parent->der = new Nodo{val,nullptr,nullptr};
                return parent->der;
            }
            parent = parent->der;
        }
    }
}

BTree::~BTree() {
    clear();
}

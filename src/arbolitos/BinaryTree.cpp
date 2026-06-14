//
// Created by elnchou on 08-06-26.
//

#include "BinaryTree.h"
#include <queue>
#include <algorithm>

void BTree::zag(Nodo *nodo) {
    Nodo *obj = nodo->izq;

    // cambiar el valor
    std::swap(nodo->value, obj->value);

    // cambiar los hijos
    std::swap(obj->izq, obj->der);

    //dar vuelta las referencias
    std::swap(nodo->der, obj->der);
    std::swap(nodo->izq, nodo->der);
}

void BTree::zig(Nodo *nodo) {
    Nodo *obj = nodo->der;

    // intercambiar el valor de los nodos
    std::swap(nodo->value, obj->value);

    // ahora "obj" debe estar a la izquierda de "nodo" en vez de su derecha
    std::swap(nodo->izq, nodo->der);

    //el valor de la izq quedó en nodo->der, debe dejarse lo más a la izq posible
    std::swap(nodo->der, obj->izq);
    //finalmente, el valor de más a la der quedó en obj->der, debe irse a nodo->der
    std::swap(obj->der, nodo->der);
}

Nodo *BTree::search(const uint val) {
    Nodo* ans = raiz;
    while (ans != nullptr && ans->value != val)
        ans = raiz->value < val ? raiz->izq : raiz->der;
    return ans;
}

void BTree::clear(const bool deleteObj) {
    std::queue<Nodo*> bfs;
    bfs.push(raiz);
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
    //agarrar el puntero al puntero de la raíz (xd)
    Nodo **parent = &raiz;

    //iterar hasta llegar a un puntero nulo
    while (*parent != nullptr)
        parent = val < (*parent)->value ? &(*parent)->izq : &(*parent)->der;

    //reasignar el puntero nulo a un nodo nuevecito
    *parent = new Nodo{val,nullptr,nullptr};

    //retornar el nodo nuevecito
    return *parent;
}

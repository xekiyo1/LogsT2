//
// Created by elnchou on 08-06-26.
//

#include "BinaryTree.h"
#include <queue>
#include <algorithm>
#include <iostream>

void BTree::zig(Nodo *nodo) {
    Nodo *obj = nodo->izq;

    Nodo *A = obj->izq, *B = obj->der , *C = nodo->der;

    // cambiar el valor
    std::swap(nodo->value, obj->value);

    nodo->izq = A;

    nodo->der = obj;
    obj->izq = B;
    obj->der = C;

    //actualizar hijos
    if (A != nullptr)A->parent = nodo;
    if (C != nullptr)C->parent = obj;
}

void BTree::zag(Nodo *nodo) {
    Nodo *obj = nodo->der;

    Nodo *A = nodo->izq, *B = obj->izq, *C = obj->der;

    // cambiar el valor
    std::swap(nodo->value, obj->value);

    nodo->izq = obj;

    obj->izq = A;
    obj->der = B;
    nodo->der = C;

    //actualizar hijos
    if (A != nullptr)A->parent = obj;
    if (C != nullptr)C->parent = nodo;
}

void BTree::zigzag(Nodo *nodo) { zag(nodo->izq); zig(nodo); }
void BTree::zagzig(Nodo *nodo) { zig(nodo->der); zag(nodo); }

Nodo *BTree::search(const uint val) {
    Nodo* ans = raiz;
    while (ans != nullptr && ans->value != val)
        ans = val < ans->value ? ans->izq : ans->der;
    return ans;
}

void BTree::clear(const bool deleteObj) {
    std::queue<Nodo*> bfs;
    if (raiz != nullptr) bfs.push(raiz);
    while (!bfs.empty()) {
        raiz = bfs.front(); bfs.pop();
        if (raiz->der != nullptr) bfs.push(raiz->der);
        if (raiz->izq != nullptr) bfs.push(raiz->izq);
        if (deleteObj) delete raiz;
    }
    raiz = nullptr;
}

Nodo* BTree::insert(const uint val) {
    //agarrar el puntero al puntero de la raíz (xd)
    Nodo **siguiente = &raiz;
    Nodo *parent = nullptr;

    //iterar hasta llegar a un puntero nulo
    while (*siguiente != nullptr) {
        parent = *siguiente;
        if (parent->value == val) return parent;
        siguiente = val < parent->value ? &parent->izq : &parent->der;
    }

    //reasignar el puntero nulo a un nodo nuevecito
    *siguiente = new Nodo{val,nullptr,nullptr,parent,1};

    //retornar el nodo nuevecito
    return *siguiente;
}


bool Nodo::operator==(const Nodo &otro) const {
    //valor distinto o una de las aristas es nula y la otra no -> falso
    if (value != otro.value
        || otro.der == nullptr xor der==nullptr
        || otro.izq == nullptr xor izq==nullptr)
        return false;
    //si no, revisar hijos
    //acá me aprovecho de que los || no evalúan el segundo término si el primero es verdadero
    return (der == nullptr || *der == *otro.der)
        && (izq == nullptr || *izq == *otro.izq);
}

bool BTree::operator==(const BTree &otro) const {
    //si uno es uno y el otro no, morirse
    if (raiz==nullptr xor otro.raiz==nullptr) return false;
    return raiz==nullptr || *raiz == *otro.raiz;
}

void Nodo::print() const {
    if (parent != nullptr && (parent->izq != this && parent->der != this))std::cout<<"me puse a llorar";
    std::cout<<value<<'(';
    if (izq!=nullptr)izq->print();
    std::cout<<',';
    if (der!=nullptr)der->print();
    std::cout<<')';
}

void BTree::print() const {
    if (raiz==nullptr) std::cout<<"NULL";
    else raiz->print();
    std::cout<<std::endl;
}
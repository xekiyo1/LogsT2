//
// Created by elnchou on 08-06-26.
//

#include "BinaryTree.h"
#include <queue>
#include <algorithm>
#include <iostream>

void BTree::zig(Nodo *nodo) {
    Nodo *obj = nodo->izq;

    // cambiar el valor
    std::swap(nodo->value, obj->value);

    // cambiar los hijos
    std::swap(obj->izq, obj->der);

    //dar vuelta las referencias
    std::swap(nodo->der, obj->der);
    std::swap(nodo->izq, nodo->der);

    //actualizar hijos
    if (nodo->izq != nullptr)nodo->izq->parent = nodo;
    if (obj->izq != nullptr)obj->izq->parent = obj;
    if (obj->der != nullptr)obj->der->parent = obj;

}

void BTree::zag(Nodo *nodo) {
    Nodo *obj = nodo->der;

    // intercambiar el valor de los nodos
    std::swap(nodo->value, obj->value);

    // ahora "obj" debe estar a la izquierda de "nodo" en vez de su derecha
    std::swap(nodo->izq, nodo->der);

    //el valor de la izq quedó en nodo->der, debe dejarse lo más a la izq posible
    std::swap(nodo->der, obj->izq);
    //finalmente, el valor de más a la der quedó en obj->der, debe irse a nodo->der
    std::swap(obj->der, nodo->der);

    //actualizar hijos
    if (nodo->der != nullptr)nodo->der->parent = nodo;
    if (obj->izq != nullptr)obj->izq->parent = obj;
    if (obj->der != nullptr)obj->der->parent = obj;
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
//
// Created by elnchou on 08-06-26.
//

#include "SplayTree.h"

void SplayTree::splay(Nodo *nodo) {
    if (nodo==nullptr) return;
    while (nodo->parent != nullptr) {
        Nodo *padre = nodo->parent;
        // existe el abuelo???
        if (Nodo *abuelo = padre->parent; abuelo == nullptr)
        {
            //ROTACIÓN SIMPLE Y TERMINAR, no hay abuelo
            if (nodo->value < padre->value) zig(padre);
            else zag(padre);
            nodo = padre;
        }
        else
        {
            // DOBLE ROTACIÓN, hay que revisar el abuelo
            if (padre->value < abuelo->value) {
                //ambos menores
                if (nodo->value < padre->value) zigzig(abuelo);
                else zigzag(abuelo);
            }else {
                //ambos mayores
                if (nodo->value > padre->value) zagzag(abuelo);
                else zagzig(abuelo);
            }
            nodo = abuelo;
        }
    }
}

void SplayTree::zigzig(Nodo *nodo) { zig(nodo); zig(nodo); }
void SplayTree::zigzag(Nodo *nodo) { zag(nodo->izq); zig(nodo); }
void SplayTree::zagzig(Nodo *nodo) { zig(nodo->der); zag(nodo); }
void SplayTree::zagzag(Nodo *nodo) { zag(nodo); zag(nodo); }

Nodo *SplayTree::insert(const uint val) {
    Nodo *nodo = BTree::insert(val);
    splay(nodo);
    return raiz;
}

Nodo *SplayTree::search(const uint val) {
    Nodo *nodo = BTree::search(val);
    splay(nodo);
    return raiz;
}

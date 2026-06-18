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
void SplayTree::zagzag(Nodo *nodo) { zag(nodo); zag(nodo); }

Nodo *SplayTree::insert(const uint val) {
    Nodo *nodo = BTree::insert(val);
    splay(nodo); //siempre existe (incluso si ya estaba en el árbol)
    return raiz;
}

Nodo *SplayTree::search(const uint val) {
    Nodo* ans = raiz, *last = nullptr;

    //buscar igual que en el OG
    while (ans != nullptr && ans->value != val) {
        last = ans;
        ans = val < ans->value ? ans->izq : ans->der;
    }

    //si no lo encontramos, hay que splayear el último visto y devolver nulo
    if (ans == nullptr) {
        splay(last);
        return nullptr;
    }

    //si lo encontramos, entonces splay() y luego devolver la nueva raíz
    splay(ans);
    return raiz;
}

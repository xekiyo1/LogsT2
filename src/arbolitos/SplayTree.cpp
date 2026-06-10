//
// Created by elnchou on 08-06-26.
//

#include "SplayTree.h"

void SplayTree::splay(Nodo *nodo) {
    Nodo *parent;
    //mientras el nodo no sea la raíz...
    while (nodo->height != 1) {
        parent = nodo->parent;
        //subir este nodo un nivel
        if (parent->der == nodo)
            zag(parent); //si está a la derecha, necesitamos un zag
        else
            zig(parent); //si está a la izquierda, necesitamos un zig
    }
    raiz = nodo;
}

Nodo *SplayTree::insert(const uint val) {
    Nodo *nodo = BTree::insert(val);
    splay(nodo);
    return nodo;
}

Nodo *SplayTree::search(const uint val) {
    Nodo *nodo = BTree::search(val);
    splay(nodo);
    return nodo;
}

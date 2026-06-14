//
// Created by elnchou on 08-06-26.
//

#include "AVL.h"

Nodo* AVL::insert(uint val){
    // Inserta el valor. Esto cambia los valores de balance
    Nodo* inserted = BTree::insert(val);

    //Revisa si estamos (potencialmente) en casos base
    if (inserted-> parent == nullptr) return inserted;

    balance(inserted->parent->parent);
    return inserted;
}

void AVL::balance(Nodo* node){
    int bf = getBalanceFactor(node); //How do i get a bf? >~<
    Nodo* child;

    if(bf>=2){
        child = node->der;

        if(getBalanceFactor(child)<0) zig(child);

        zag(node);
    }else if(bf<=-2){
        child = node->izq;

        if(getBalanceFactor(child)>0) zag(child);


        zig(node);
    }

}


int AVL::getBalanceFactor(Nodo* node){
    if (node == nullptr) return 0;
    return getHeight(node->der)-getHeight(node->izq);
}
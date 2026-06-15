//
// Created by elnchou on 08-06-26.
//

#include "AVL.h"
#include <cmath>

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

    if(std::abs(bf)<=1) return;
    
    Nodo* parent = node->parent;
    Nodo* child;

    if(bf>=2){

        // If the balance is disturbed left-wise, takes the right child
        child = node->der;

        // Then, searches for the biggest child. If balance factor is less than 0
        // It means the disturber is to the left, so a rotation is necessary
        if(getBalanceFactor(child)<0) zig(child);

        //Rotates
        zag(node);
    }else if(bf<=-2){
        child = node->izq;

        if(getBalanceFactor(child)>0) zag(child);


        zig(node);
    }

    balance(parent);

}


int AVL::getBalanceFactor(Nodo* node){
    if (node == nullptr) return 0;
    return getHeight(node->der)-getHeight(node->izq);
}
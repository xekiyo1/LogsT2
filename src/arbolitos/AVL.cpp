//
// Created by elnchou on 08-06-26.
//

#include "AVL.h"
#include <cmath>

Nodo* AVL::insert(uint val){
    // Inserta el valor. Esto cambia los valores de balance
    Nodo* inserted = BTree::insert(val);

    updateHeight(inserted);

    //Revisa si estamos (potencialmente) en casos base
    if (inserted -> parent != nullptr)
        balance(inserted->parent->parent);

    return inserted;
}

void AVL::balance(Nodo* node) {
    int bf = getBalanceFactor(node); //How do i get a bf? >~<

    if(std::abs(bf)<=1) return;

    if(bf>=2){
        // If the balance is disturbed left-wise, we need to check the right child.
        // If balance factor is less than 0 It means the disturber is to the left,
        // so a double rotation is necessary
        if(getBalanceFactor(node->der) < 0) zagzig(node); //RL -> zagzig
        //otherwise, a simple rotation is enough
        else zag(node); //RR
    }else if(bf<=-2){
        if(getBalanceFactor(node->izq) > 0) zigzag(node); //LR -> zig-zag
        else zig(node); //LL
    }

    balance(node->parent);

}


int AVL::getBalanceFactor(const Nodo* node){
    if (node == nullptr) return 0;
    //esto hace underflow, pero la función retorna "int" así que se arregla solo
    return getHeight(node->der)-getHeight(node->izq);
}

uint AVL:: getHeight(const Nodo* node){
    if(node == nullptr) return 0;
    return node->height;
}

void AVL::updateHeight(Nodo* node){
    if (node==nullptr) return;

    //height of left son
    uint lh = getHeight(node->izq);
    //height of the right son
    uint rh = getHeight(node->der);
    //my new height
    uint curr_height = 1 + std::max(lh, rh);

    // If height would not change, do nothing
    if (node->height == curr_height)return;

    //Updates height of the node
    node->height = curr_height;
    return updateHeight(node->parent);
}
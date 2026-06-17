//
// Created by elnchou on 08-06-26.
//

#include "AVL.h"
#include <cmath>
#include <stdexcept>

Nodo* AVL::insert(uint val){
    // Inserta el valor. Esto cambia los valores de balance
    Nodo* inserted = BTree::insert(val);

    balance(inserted); //aquí adentro se actualiza la altura y rotaciones

    return inserted;
}

void AVL::balance(Nodo* node) {
    for (;node != nullptr ; node = node->parent) {
        updateHeight(node);

        int bf = getBalanceFactor(node); //How do i get a bf? >~<
        //printf("Nodo: %u Altura: %u Bf: %d\n",node->value,node->height,bf);

        //if(std::abs(bf)<=1) return;
        if(std::abs(bf)<=1) continue;

        if(bf==-2){
            // If the balance is disturbed left-wise, we need to check the right child.
            // If balance factor is less than 0 It means the disturber is to the left,
            // so a double rotation is necessary
            if(getBalanceFactor(node->der) > 0) zagzig(node); //RL -> zagzig
            //otherwise, a simple rotation is enough
            else zag(node); //RR
        }else if(bf==2){
            if(getBalanceFactor(node->izq) < 0) zigzag(node); //LR -> zig-zag
            else zig(node); //LL
        }else //avisar si lo tenemos mal implementado (bf imposible unu)
            throw std::runtime_error("Error balanceando AVLs");

        //actualizar alturas post-rotación
        updateHeight(node->der);
        updateHeight(node->izq);
        updateHeight(node);
    }
}


int AVL::getBalanceFactor(const Nodo* node){
    if (node == nullptr) return 0;
    //esto hace underflow, pero la función retorna "int" así que se arregla solo
    return getHeight(node->izq)-getHeight(node->der);
}

uint AVL:: getHeight(const Nodo* node){
    if(node == nullptr) return 0;
    return node->height;
}

void AVL::updateHeight(Nodo* node, const bool recursive){
    if (node==nullptr) return;

    //height of left son
    uint lh = getHeight(node->izq);
    //height of the right son
    uint rh = getHeight(node->der);
    //my old and new height
    uint old_height = node->height;
    node->height = 1 + std::max(lh, rh);

    // If height changed, update parents (if recursive)
    if (recursive && node->height != old_height)
        return updateHeight(node->parent);
}
//
// Created by elnchou on 08-06-26.
//

#ifndef LOGST2_AVL_H
#define LOGST2_AVL_H
#include "BinaryTree.h"

class AVL : public BTree{
protected:
    /**
        gets the balance factor for a given AVL tree.
        @param node: The node to inspect for balance factor
    */
    static int getBalanceFactor(const Nodo* node);
    /**
        Balances the tree.
    */
    static void balance(Nodo* node);
    /**
    * Gets a node height
    * @param nodo The node to be inspected
    */
    static uint getHeight(const Nodo *nodo);
    /**
        Actualiza la altura de un nodo y, si ha sido actualizada, actualiza además la de su padre.
        @param node El nodo cuya altura será actualizada.
        @param recursive Indica si se deben actualizar los padres también.
    */
    static void updateHeight(Nodo* node, bool recursive = false);
public:
    Nodo* insert(uint val) override;
};


#endif //LOGST2_AVL_H

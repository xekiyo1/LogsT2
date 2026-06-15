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
    static int getBalanceFactor(Nodo* node);

    /**
        Balances the tree.
    */
    static void balance(Nodo* node);
public:
    Nodo* insert(uint val) override;
};



#endif //LOGST2_AVL_H

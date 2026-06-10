//
// Created by elnchou on 08-06-26.
//

#ifndef LOGST2_SPLAYTREE_H
#define LOGST2_SPLAYTREE_H
#include "BinaryTree.h"

class SplayTree : public BTree {
private:
    void splay(Nodo *nodo);
public:
    Nodo *insert(uint val) override;
    Nodo *search(uint val) override;
};

#endif //LOGST2_SPLAYTREE_H

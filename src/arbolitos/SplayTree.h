//
// Created by elnchou on 08-06-26.
//

#ifndef LOGST2_SPLAYTREE_H
#define LOGST2_SPLAYTREE_H
#include "BinaryTree.h"

class SplayTree : public BTree {
private:
    /**
     * Lleva a un nodo hasta la raíz del árbol mediante rotaciones dobles.
     * @param nodo Nodo que se llevará hasta la cima del mundo
     */
    static void splay(Nodo *nodo);

    /**
     * Realiza la operación "zig" en esta posición de memoria, dos veces.
     * @param nodo Nodo que será rotado
     */
    static void zigzig(Nodo* nodo);
    /**
     * Realiza la operación y luego "zig" "zag" en una posición de memoria, dos veces.
     * @param nodo Nodo que será rotado.
     */
    static void zigzag(Nodo* nodo);
    /**
     * Realiza la operación y luego "zag" "zig" en una posición de memoria, dos veces.
     * @param nodo Nodo que será rotado.
     */
    static void zagzig(Nodo* nodo);
    /**
     * Realiza la operación "zag" en esta posición de memoria, dos veces.
     * @param nodo Nodo que será rotado.
     */
    static void zagzag(Nodo* nodo);

public:
    Nodo *insert(uint val) override;
    Nodo *search(uint val) override;
};

#endif //LOGST2_SPLAYTREE_H

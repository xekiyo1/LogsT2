//
// Created by elnchou on 08-06-26.
//

#ifndef LOGST2_SPLAYTREE_H
#define LOGST2_SPLAYTREE_H
#include "BinaryTree.h"

/**
 * Clase que representa al objeto de estudio: un Splay Tree.
 * Extiende de BTree y realiza rotaciones dobles luego de cada búsqueda e inserción
 * para llevar el último nodo visto hasta la raíz (incluye al recién insertado, si aplica).
 *
 * Tiene el enfoque bottom-up (rotaciones desde el nodo a la raíz, en vez de al revés).
 */
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
     * Realiza la operación "zag" en esta posición de memoria, dos veces.
     * @param nodo Nodo que será rotado.
     */
    static void zagzag(Nodo* nodo);

public:
    Nodo *insert(uint val) override;
    Nodo *search(uint val) override;
};

#endif //LOGST2_SPLAYTREE_H

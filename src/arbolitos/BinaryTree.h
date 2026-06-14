//
// Created by elnchou on 08-06-26.
//

#ifndef LOGST2_BINARYTREE_H
#define LOGST2_BINARYTREE_H

#include "../../macros.hp"

/**
 * Representación de un Nodo en datos, que contiene punteros a otros dos nodos.
 */
struct Nodo{
    /// Valor numérico que contiene el nodo. Cuidado que puede usar el rango completo de uint.
    unsigned int value;
    /// Adjacencia del nodo, que contiene valores menores al actual.
    struct Nodo *izq;
    /// Adjacencia del nodo, que contiene valores mayores al actual.
    struct Nodo *der;
    //Nodo padre para hacer muy muy faciles las rotaciones
    struct Nodo *parent;
    //Altura para uso en árboles AVL
    uint height;
};

/**
 * Clase que actúa como la base para el resto de árboles. Básicamente, es para no tener que rehacer
 * funciones de borrado y la de búsqueda.
 */
class BTree {
protected:
    /// Nodo inicial del árbol, desde el que comienza a buscar.
    Nodo *raiz = nullptr;
    /**
     * Realiza una rotación "zig" en este nodo, dejando su nodo de la izquierda en la posición del original.
     *
     * NOTA: Esto intercambia las direcciones de memoria y los punteros, así que no es necesario actualizar el padre.
     * @param nodo Puntero al nodo que se modificará.
     */
    static void zig(Nodo *nodo);
    /**
     * Realiza una rotación "zag" en este nodo, dejando su nodo de la derecha en la posición del original.
     *
     * NOTA: Esto intercambia las direcciones de memoria y los punteros, así que no es necesario actualizar el padre.
     * @param nodo Puntero al nodo que se modificará.
     */
    static void zag(Nodo *nodo);
public:
    /**
     * Función desforestadora. Es decir, elimina el árbol borrando todos los nodos.
     * @param deleteObj Indica si se deben desalocar los nodos, es decir, hacer llamados a "delete Nodo".
     */
    void clear(bool deleteObj = true);
    /**
     * Busca un valor dentro del árbol de búsqueda binaria, aprovechando el ordenamiento de nodos.
     * @param val Valor numérico a buscar en el árbol
     * @return Puntero al nodo que contiene el valor encontrado. Devuelve nullptr si no existe.
     */ //necesitamos retornar realmente el nodo?
    virtual Nodo *search(uint val);

    /**
     *
     * @param val Valor numérico a insertar en el árbol.
     * @return Busca la posición de un valor y lo añade al árbol. ¿Qué pasa si está repetido?
     * @note Podría re-balancear el árbol si es una subclase de BTree.
     */
    virtual Nodo* insert(uint val);

    /**
     * Destructor. Libera toda la memoria ocupada por los nodos.
     */
    virtual ~BTree() {clear();}
};

#endif //LOGST2_BINARYTREE_H

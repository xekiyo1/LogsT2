//
// Created by elnchou on 14-06-26.
//
#include <assert.h>
#include "../arbolitos/SplayTree.h"
#include <iostream>
#include <vector>

SplayTree arbolito;
/**
 * Comprueba que el SplayTree haya realizado las rotaciones correctas para quedar en una estructura
 * específica, a base de crear un BTree con inserciones distintas.
 * @param valores Valores que serán insertados en un BTree normal, en orden.
 */
void check(std::vector<uint> valores) {
    BTree comprobador;
    for (uint x : valores) comprobador.insert(x);
    arbolito.print();
    comprobador.print();

    assert(arbolito == comprobador);

    comprobador.clear();
}

/// Utilizamos este programa para comprobar el funcionamiento de los zig y zags. Veamos cómo va...
int main(){
    //para probar que funcionan bien el zig y el zag
    arbolito.insert(2);
    arbolito.insert(3); //2(,3) -> zag -> 3(2,)
    check({3,2});
    arbolito.clear();

    arbolito.insert(6);
    arbolito.insert(2); //2(,6)
    check({2,6});
    //ahora si inserto algo entre 2 y 6, tendré que hacer un zag-zig
    arbolito.insert(4); //2(,6(4,)) -> zagzig -> 4(2(),6())

    check({4,2,6});

    //ahora, si inserto algo mayor a 2, tendré que hacer zig-zag
    arbolito.insert(3); // 4(2(,3),6(,)) -> zig-zag -> 3(2,4(,6))
    check({3,2,4,6});
    //3(2,4(,6(5,))) -> [4(,6(5,)) -> 5(4,6)]
    //-> 3(2,5(4,6)) -> 5(3(2,4), 6)
    arbolito.insert(5);
    check({5,3,2,4,6});
    std::cout << "Todo funcionó!" << std::endl;
}
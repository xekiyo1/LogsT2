//
// Created by elnchou on 14-06-26.
//
#include <assert.h>

#include "../arbolitos/SplayTree.h"

SplayTree hola;
void insert(uint i) {
    hola.insert(i);
    hola.print();
}

int main(){
    //para probar que funcionan bien el zig y el zag

    insert(5);
    insert(2); //2(,5)
    insert(7); //2(,5(,7)) -> 7(5(2,),)
    insert(20);
    insert(8);
    insert(9);
    insert(10);
}
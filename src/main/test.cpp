//
// Created by elnchou on 14-06-26.
//
#include <assert.h>

#include "../arbolitos/SplayTree.h"

int main(){
    //para probar que funcionan bien el zig y el zag
    SplayTree hola;
    hola.insert(5);
    hola.insert(2); //2(,5)
    hola.insert(7); //2(,5(,7)) -> 7(5(2,),)
    BTree tester; tester.insert(7); tester.insert(5); tester.insert(2);
    assert(hola == tester);


}
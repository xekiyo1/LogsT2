//
// Created by elnchou on 10-06-26.
//

#include "RandomArray.h"

uint RandomValues::generateRandUint() {
    //TODO: crear cosito al azar y retornarlo
    return 0;
}

RandomValues::RandomValues(const std::size_t howMany) {
    N = howMany;
    dataset.resize(N);
    for (auto &x : dataset) x = generateRandUint();
    // TODO: inicializar probabilidades
}

uint RandomValues::generateIdx() {
    // TODO: llamar a la generador de probabilidades o lo que sea que tenemos y retornar el índice
    return 0;
}

ullong RandomValues::calcProb(uint i) {

}

std::vector<uint> RandomValues::getVal(std::size_t quantity) {
    std::vector<uint> ans(quantity);
    for (uint &x : ans) x = operator[](generateIdx());
    return ans;
}

const uint &RandomValues::operator[](uint i) {
    return dataset[i];
}

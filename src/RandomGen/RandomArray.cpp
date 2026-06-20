//
// Created by elnchou on 10-06-26.
//

#include "RandomArray.h"

uint RandomValues::generateRandUint() {
    return rng();
}

RandomValues::RandomValues(const std::size_t howMany, const uint seed) {
    dataset.resize(howMany);
    rng = std::mt19937_64(seed);
    for (auto &x : dataset) x = generateRandUint();
    updateProbs();
}

RandomValues::RandomValues(const std::vector<uint> &data, const uint seed) {
    dataset = data;
    rng = std::mt19937_64(seed);
    updateProbs();
}

void RandomValues::updateProbs() {
    N = dataset.size();
    std::vector<dab> weight(N);

    // peso relativo e^(-lambda * i)
    for (size_t i = 0; i < N; ++i)
        weight[i] = exp(-lambda * i);

    probs = std::discrete_distribution<uint>(weight.begin(), weight.end());
}


uint RandomValues::generateIdx(const bool uniform) {
    // notar que como N es potencia de dos, & N-1 es lo mismo que % N
    // y como uint también es potencia de dos, es una generación uniforme en cualquier rango de bits
    return uniform ? generateRandUint() & N-1 : probs(rng);
}

std::vector<uint> RandomValues::getVal(const std::size_t quantity, const bool uniformDist) {
    std::vector<uint> ans(quantity);
    for (uint &x : ans) x = operator[](generateIdx(uniformDist));
    return ans;
}

uint RandomValues::generate(const bool uniformDist) {
    return operator[](generateIdx(uniformDist));
}

const uint &RandomValues::operator[](const uint i) const {
    return dataset[i];
}

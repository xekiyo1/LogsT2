//
// Created by elnchou on 10-06-26.
//

#include "RandomArray.h"

    std::random_device rd;
    std::mt19937 gen(rd());

uint RandomValues::generateRandUint() {
    return gen();
}

RandomValues::RandomValues(const std::size_t howMany) {
    N = howMany;
    dataset.resize(N);
    for (auto &x : dataset) x = generateRandUint();

    std::vector<double> probab;
    probab.reserve(N);

    for (size_t i = 0; i < N; ++i) {
        // peso relativo e^(-lambda * i)
        probab.push_back(exp(-lambda * i)); 
    }    
    
    probs = std::discrete_distribution<uint>(probab.begin(), probab.end());
}

uint RandomValues::generateIdx(const bool uniform) {
    // notar que como N es potencia de dos, & N-1 es lo mismo que % N
    // y como uint también es potencia de dos, es una generación uniforme en cualquier rango de bits
    return uniform ? generateRandUint() & N-1 : probs(gen);
}

std::vector<uint> RandomValues::getVal(const std::size_t quantity, const bool uniformDist) {
    std::vector<uint> ans(quantity);
    for (uint &x : ans) x = operator[](generateIdx(uniformDist));
    return ans;
}

const uint &RandomValues::operator[](const uint i) const {
    return dataset[i];
}

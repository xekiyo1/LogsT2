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

uint RandomValues::generateIdx() {
    return probs(gen);
}

/*
ullong RandomValues::calcProb(uint i) {

    ullong peso = exp(-lambda * i);

    return peso/static_cast<double>(N);

}*/

std::vector<uint> RandomValues::getVal(std::size_t quantity) {
    std::vector<uint> ans(quantity);
    for (uint &x : ans) x = operator[](generateIdx());
    return ans;
}

const uint &RandomValues::operator[](uint i) const {
    return dataset[i];
}

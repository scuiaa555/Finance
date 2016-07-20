//
// Created by CUI Shidong on 12/7/2016.
//

#ifndef FINANCE_RANDOMSEQUENCEGENERATOR_H
#define FINANCE_RANDOMSEQUENCEGENERATOR_H

#include "UniformLEcuyerRNG1.h"
#include <vector>

using std::vector;

/* decorator pattern */
template <typename RNG>
class RandomSequenceGenerator {
public:
    RandomSequenceGenerator(vector<double>::size_type dimensionality, const RNG &rng);

    const vector<double> &nextSequence();

private:
    RNG rng_;
    vector<double>::size_type dimensionality_;
    vector<double> sequence_;

};

template<typename RNG>
RandomSequenceGenerator<RNG>::RandomSequenceGenerator(vector<double>::size_type dimensionality, const RNG &rng) : dimensionality_(
        dimensionality), rng_(rng) {
    sequence_.resize(dimensionality_);
}

template <typename RNG>
const vector<double> &RandomSequenceGenerator<RNG>::nextSequence() {
    for (int i = 0; i < dimensionality_; i++) {
        sequence_[i] = rng_.next();
    }
    return sequence_;
}

#endif //FINANCE_RANDOMSEQUENCEGENERATOR_H

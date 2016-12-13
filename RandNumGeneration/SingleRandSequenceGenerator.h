//
// Created by CUI Shidong on 12/7/2016.
//

#ifndef FINANCE_RANDOMSEQUENCEGENERATOR_H
#define FINANCE_RANDOMSEQUENCEGENERATOR_H

#include "UniformLEcuyerRNG1.h"
#include <vector>

using std::vector;

/* decorator pattern */
template<typename RNG>
class SingleRandSequenceGenerator {
public:
    SingleRandSequenceGenerator(vector<double>::size_type dimension, const RNG &rng);

    const vector<double> &next();

    const vector<double> &last() { return sequence_; }

    unsigned long getDimension() const { return dimension_; }

private:
    RNG rng_;
    unsigned long dimension_;
    vector<double> sequence_;
};

template<typename RNG>
SingleRandSequenceGenerator<RNG>::SingleRandSequenceGenerator(vector<double>::size_type dimension, const RNG &rng)
        : dimension_(
        dimension), rng_(rng) {
    sequence_.resize(dimension_);
}

template<typename RNG>
const vector<double> &SingleRandSequenceGenerator<RNG>::next() {
    for (int i = 0; i < dimension_; i++) {
        sequence_[i] = rng_.next();
    }
    return sequence_;
}

#endif //FINANCE_RANDOMSEQUENCEGENERATOR_H

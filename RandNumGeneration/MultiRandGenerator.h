//
// Created by CUI Shidong on 13/12/2016.
//

#ifndef FINANCE_MULTIRANDGENERATOR_H
#define FINANCE_MULTIRANDGENERATOR_H

#include "SingleRandSequenceGenerator.h"

using std::shared_ptr;

template<typename ...Args>
class MultiRandGenerator {
public:
    MultiRandGenerator();

    template<typename T>
    void setRandGenerators() {
        ++numOfSingleRNG_;
        rsgs_.push_back(shared_ptr<RNGComponent>(new SingleRandSequenceGenerator<T>(0)));
    }

    template<typename T, typename ...Args>
    void setRandGenerators() {
        ++numOfSingleRNG_;
        rsgs_.push_back(shared_ptr<RNGComponent>(new SingleRandSequenceGenerator<T>(0)));
        setRandGenerators<Args>();
    };

    const vector<double> &next();

    const vector<double> &last() const { return sequence_; }

private:
    vector<shared_ptr<RNGComponent>> rsgs_;
    vector<double> sequence_;
    unsigned long dimension_;
    unsigned long numOfSingleRNG_;     /*!< dimension of different single random sequence generators */
};

template <typename ...Args>
MultiRandGenerator::MultiRandGenerator() :
        dimension_(0), numOfSingleRNG_(0) {
    setRandGenerators<Args>();
}

const vector<double> &MultiRandGenerator::next() {
    sequence_.clear();
    sequence_.reserve(dimension_);
    for (vector<shared_ptr<RNGComponent>>::iterator iter = rsgs_.begin(); iter != rsgs_.end(); ++iter) {
        (*iter)->next();
        std::copy((*iter)->last().begin(), (*iter)->last().end(), std::back_inserter(sequence_));
    }
    return sequence_;
}

#endif //FINANCE_MULTIRANDGENERATOR_H

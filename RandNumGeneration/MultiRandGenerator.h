//
// Created by CUI Shidong on 13/12/2016.
//

#ifndef FINANCE_MULTIRANDGENERATOR_H
#define FINANCE_MULTIRANDGENERATOR_H

#include "SingleRandSequenceGenerator.h"

using std::shared_ptr;

//template<typename T>
//void setRandGenerators<T>(vector<shared_ptr<RNGComponent>> &rsgs, unsigned long &numOfSingleRNG) {
//    ++numOfSingleRNG;
//    rsgs.push_back(shared_ptr<RNGComponent>(new SingleRandSequenceGenerator<T>(0)));
//}
//
//template<typename T, typename ...Args>
//void setRandGenerators<T, Args>(vector<shared_ptr<RNGComponent>> &rsgs, unsigned long &numOfSingleRNG) {
//    ++numOfSingleRNG;
//    rsgs.push_back(shared_ptr<RNGComponent>(new SingleRandSequenceGenerator<T>(0)));
//    setRandGenerators<Args>(rsgs, numOfSingleRNG);
//}

template<typename ...Args>
class MultiRandGenerator {
public:
    MultiRandGenerator() : rsgs_({shared_ptr<Args>(new Args())...}), numOfSingleRNG_(rsgs_.size()) { }

//    template<typename T>
//    void setRandGenerators() {
//        ++numOfSingleRNG_;
//        rsgs_.push_back(shared_ptr<RNGComponent>(new SingleRandSequenceGenerator<T>(0)));
//    }
//
//    template<typename T, typename ...Args>
//    void setRandGenerators() {
//        ++numOfSingleRNG_;
//        rsgs_.push_back(shared_ptr<RNGComponent>(new SingleRandSequenceGenerator<T>(0)));
//        setRandGenerators<Args>();
//    };

    const vector<double> &next();

    const vector<double> &last() const { return sequence_; }

    vector<shared_ptr<RNGComponent>> &getRsgs() { return rsgs_; }

//    friend void setRandGenerators<Args>(vector<shared_ptr<RNGComponent>> &rsgs, unsigned long &numOfSingleRNG);


private:
    vector<shared_ptr<RNGComponent>> rsgs_;
    vector<double> sequence_;
    unsigned long dimension_;
    unsigned long numOfSingleRNG_;     /*!< dimension of different single random sequence generators */
};

//template<typename ...Args>
//MultiRandGenerator<Args>::MultiRandGenerator() :
//        dimension_(0), numOfSingleRNG_(0) {
//    setRandGenerators<Args>(rsgs_, numOfSingleRNG_);
//}

template<typename ...Args>
const vector<double> &MultiRandGenerator<Args...>::next() {
    sequence_.clear();
    sequence_.reserve(dimension_);
    for (vector<shared_ptr<RNGComponent>>::iterator iter = rsgs_.begin(); iter != rsgs_.end(); ++iter) {
        (*iter)->next();
        std::copy((*iter)->last().begin(), (*iter)->last().end(), std::back_inserter(sequence_));
    }
    return sequence_;
}

#endif //FINANCE_MULTIRANDGENERATOR_H

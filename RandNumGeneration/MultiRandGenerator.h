//
// Created by CUI Shidong on 13/12/2016.
//

#ifndef FINANCE_MULTIRANDGENERATOR_H
#define FINANCE_MULTIRANDGENERATOR_H

#include "SingleRandSequenceGenerator.h"
#include <tuple>

using std::shared_ptr;
using std::tuple;


template<typename ...Args>
class MultiRandGenerator : public RandomVariableGenerator<vector<double>> {
public:
//    MultiRandGenerator() : rngs_(),
//                           numOfSingleRNG_(sizeof...(Args)), rngArguments_(numOfSingleRNG_),
//                           RandomVariableGenerator<vector<double>>() {
//        for (int i = 0; i < numOfSingleRNG_; ++i) {
//            dimension_ += rngs_[i]->dimension_;
//        }
//    }

    vector<GenericRandomVariableGenerator::Argument *> getArgument() {
        return rngArguments_;
    }

    const vector<double> &next() override;


    const vector<double> &last() override { return sequence_; }

private:
    tuple<Args...> rngs_;
    vector<double> sequence_;
//    unsigned long dimension_;
    unsigned long numOfSingleRNG_;
    /*!< dimension of different single random sequence generators */
    vector<GenericRandomVariableGenerator::Argument *> rngArguments_;



    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I < sizeof...(Tp), void>::type
    nextRNG(std::tuple<Tp...> &t) {
        merge(std::get<I>(t).next());
        nextRNG<I + 1, Tp...>(t);
    }

    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I == sizeof...(Tp), void>::type
    nextRNG(std::tuple<Tp...> &t) {}

    void merge(double val) {
        sequence_.push_back(val);
    }

    void merge(vector<double> vals) {
        std::copy(vals.begin(), vals.end(), std::back_inserter(sequence_));
    }
};


template<typename ...Args>
const vector<double> &MultiRandGenerator<Args...>::next() {
    sequence_.clear();
    sequence_.reserve(dimension_);
    nextRNG(rngs_);
    return sequence_;
}

#endif //FINANCE_MULTIRANDGENERATOR_H


//    MultiRandGenerator() : rngs_({shared_ptr<Args>(new Args())...}),
//                           numOfSingleRNG_(rngs_.size()), rngArguments_(numOfSingleRNG_),
//                           RandomVariableGenerator<vector<double>>() {
//        for (int i = 0; i < numOfSingleRNG_; ++i) {
//            dimension_ += rngs_[i]->dimension_;
//        }
//    }
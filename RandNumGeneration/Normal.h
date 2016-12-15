//
// Created by CUI Shidong on 15/12/2016.
//

#ifndef FINANCE_NORMAL_H
#define FINANCE_NORMAL_H

#include "RandNumGeneration/RandomVariableGenerator.h"
#include "RandNumGeneration/NormalMarsagliaBrayRng.h"
#include <cmath>

//template<typename NormMethod = NormalMarsagliaBrayRng<UniformLEcuyerRNG1>>
class GenericNormal : public RandomVariableGenerator<double> {
public:
    GenericNormal() : mean_(0.0), variance_(1.0) { }

//    typedef double rng_return_type;

//    const double &next() override;

//    const double &last() override;

//    void getArgument(Model::Argument *arg) override;

    class Argument : public Model::Argument {
    public:
        double mean_;
        double variance_;
    };

protected:
//    NormMethod rng_;
    double mean_;
    double variance_;
//    double last_;
};

template<typename NormMethod = NormalMarsagliaBrayRng<UniformLEcuyerRNG1>>
class Normal : public GenericNormal {
public:
    Normal() : GenericNormal(), rng_(), last_(0.0) { }

    typedef double rng_return_type;

    const double &next() override;

    const double &last() override;

    void getArgument(Model::Argument *arg) override;

//    class Argument : public Model::Argument {
//    public:
//        double mean_;
//        double variance_;
//    };

private:
    NormMethod rng_;
//    double mean_;
//    double variance_;
    double last_;
};


template<typename NormMethod>
const double &Normal<NormMethod>::next() {
    last_ = rng_.next() * sqrt(variance_) + mean_;
    return last_;
}

template<typename NormMethod>
const double &Normal<NormMethod>::last() {
    return last_;
}

template<typename NormMethod>
void Normal<NormMethod>::getArgument(Model::Argument *arg) {
    GenericNormal::Argument *argument = dynamic_cast<GenericNormal::Argument *>(arg);   //need to check!!!
    mean_ = argument->mean_;
    variance_ = argument->variance_;

}

#endif //FINANCE_NORMAL_H

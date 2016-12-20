//
// Created by CUI Shidong on 20/12/2016.
//

#ifndef FINANCE_COMPOUNDPOISSON_H
#define FINANCE_COMPOUNDPOISSON_H

#include "RandNumGeneration/RandomVariableGenerator.h"
#include "RandNumGeneration/Poisson.h"


class GenericCompoundPoisson : public RandomVariableGenerator<double> {
public:
    GenericCompoundPoisson() : RandomVariableGenerator<double>(1) {}

    class Argument : public GenericRandomVariableGenerator::Argument {
    public:
        GenericPoisson::Argument *argPtrPoisson_;
        GenericRandomVariableGenerator::Argument *argPtrJump_;
    };

    virtual GenericRandomVariableGenerator::Argument *getArgument()=0;

protected:
    Argument argument_;
};


template<typename PoissonRNG, typename JumpRNG>
class CompoundPoisson : public GenericCompoundPoisson {
public:
    CompoundPoisson() : GenericCompoundPoisson(), rngPoisson_(), rngJump_(), last_(0.0) {
        argument_.argPtrPoisson_ = dynamic_cast<GenericPoisson::Argument *>(rngPoisson_.getArgument());
        argument_.argPtrJump_ = rngJump_.getArgument();
    }

    typedef double rng_return_type;

    const double &next() override;

    const double &last() override;

    virtual GenericRandomVariableGenerator::Argument *getArgument() override;

private:
    PoissonRNG rngPoisson_;
    JumpRNG rngJump_;
    double last_;
};


template<typename PoissonRNG, typename JumpRNG>
const double &CompoundPoisson<PoissonRNG, JumpRNG>::next() {
    int n = round(rngPoisson_.next());
    last_ = 0.0;
    for (int i = 0; i < n; ++i) {
        last_ += rngJump_.next();
    }
    return last_;
}

template<typename PoissonRNG, typename JumpRNG>
const double &CompoundPoisson<PoissonRNG, JumpRNG>::last() {
    return last_;
}

template<typename PoissonRNG, typename JumpRNG>
GenericRandomVariableGenerator::Argument *CompoundPoisson<PoissonRNG, JumpRNG>::getArgument() {
    return &argument_;
}

#endif //FINANCE_COMPOUNDPOISSON_H

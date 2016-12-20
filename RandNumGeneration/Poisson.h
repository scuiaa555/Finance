//
// Created by CUI Shidong on 20/12/2016.
//

#ifndef FINANCE_POISSON_H
#define FINANCE_POISSON_H

#include "RandNumGeneration/RandomVariableGenerator.h"
#include <cmath>
#include "RandNumGeneration/UniformLEcuyerRNG1.h"
#include "PoissonInverse.h"

class GenericPoisson : public RandomVariableGenerator<double> {
public:
    GenericPoisson() : RandomVariableGenerator<double>(1) {}

    class Argument : public GenericRandomVariableGenerator::Argument {
    public:
        Argument() : lambda_(0.0) {}

        Argument(double lambda) : lambda_(lambda) {}

        double lambda_;
    };

    virtual GenericRandomVariableGenerator::Argument *getArgument()=0;

protected:
    Argument argument_;
};


template<typename PoissonMethod = PoissonInverse<UniformLEcuyerRNG1>>
class Poisson : public GenericPoisson {
public:
    Poisson() : GenericPoisson(), rng_(), last_(0.0) {}

    Poisson(double lambda) : GenericPoisson(), rng_(), last_(0.0) {}

    typedef double rng_return_type;

    const double &next() override;

    const double &last() override;

    virtual GenericRandomVariableGenerator::Argument *getArgument() override;

private:
    PoissonMethod rng_;
    double last_;
};


template<typename PoissonMethod>
const double &Poisson<PoissonMethod>::next() {
    last_ = rng_.next(argument_.lambda_);
    return last_;
}

template<typename PoissonMethod>
const double &Poisson<PoissonMethod>::last() {
    return last_;
}

template<typename PoissonMethod>
GenericRandomVariableGenerator::Argument *Poisson<PoissonMethod>::getArgument() {
    return &argument_;
}

#endif //FINANCE_POISSON_H

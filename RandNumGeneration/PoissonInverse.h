//
// Created by CUI Shidong on 20/12/2016.
//

#include <cmath>

#ifndef FINANCE_POISSONINVERSE_H
#define FINANCE_POISSONINVERSE_H

template<typename UniformRNG>
class PoissonInverse {
public:
    PoissonInverse() : rng_(), last_(0.0) {}

//    PoissonInverse(double lambda) : rng_(), lambda_(lambda), last_(0.0) {}

    double next(double lambda);

    double last() { return last_; }

private:
    UniformRNG *rng_;
    double last_;        /**< last return value. */
//    double lambda_;
};

template<typename UniformRNG>
double PoissonInverse<UniformRNG>::next(double lambda) {
    double u = rng_->getInstance().next();
    double poisson = 0;
    double expTerm = exp(-lambda);
    double current = 1.0;
    double cum = expTerm;
    while (cum < u) {
        poisson += 1.0;
        current = current * lambda / poisson;
        cum += (current * expTerm);
    }
    last_ = poisson;
    return last_;
}

#endif //FINANCE_POISSONINVERSE_H
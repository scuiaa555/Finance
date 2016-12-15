//
// Created by CUI Shidong on 14/12/2016.
//

#ifndef FINANCE_PSEUDORANDOM_H
#define FINANCE_PSEUDORANDOM_H

#include <vector>
#include "RandNumGeneration/MultiRandGenerator.h"
#include "Model.h"

template<typename RNG>
struct SingleRandom {
    typedef RNG rng_type;
    typedef typename RNG::rng_return_type rng_return_type;
    typedef vector<Model::Argument *> rng_argument_type;
};

template<typename ...RNGs>
struct MultiRandom {
    typedef MultiRandGenerator<RNGs...> rng_type;
    typedef std::vector<double> rng_return_type;
    typedef Model::Argument *rng_argument_type;
};

#endif //FINANCE_PSEUDORANDOM_H

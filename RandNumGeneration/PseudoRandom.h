//
// Created by CUI Shidong on 14/12/2016.
//

#ifndef FINANCE_PSEUDORANDOM_H
#define FINANCE_PSEUDORANDOM_H

#include <vector>

template<typename RNG>
struct SingleRandom {
    typedef RNG rng_type;
    typedef double rng_return_type;
};

template<typename RNG>
struct MultiRandom {
    typedef RNG rng_type;
    typedef std::vector<double> rng_return_type;
};

#endif //FINANCE_PSEUDORANDOM_H

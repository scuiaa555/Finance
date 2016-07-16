//
// Created by CUI Shidong on 12/7/2016.
//

#ifndef FINANCE_NORMALINVERSEMARSAGLIABRAY_H
#define FINANCE_NORMALINVERSEMARSAGLIABRAY_H

#include "RandNumGeneration/UniformLEcuyerRNG1.h"
#include <cmath>

template<typename UniformRNG>
class NormalMarsagliaBrayRng {
public:
    NormalMarsagliaBrayRng() : rng_() {
        z_ = 0.0;
        secondExists_ = false;
    }

    double next();

private:
    UniformRNG rng_;
    double z_;
    bool secondExists_;

};

template<typename UniformRNG>
double NormalMarsagliaBrayRng<UniformRNG>::next() {

    if (secondExists_) {
        secondExists_ = !secondExists_;
        return z_;
    }
    secondExists_ = !secondExists_;
    double x, u1, u2;
    do {
        u1 = 2.0 * rng_.next() - 1;
        u2 = 2.0 * rng_.next() - 1;
        x = u1 * u1 + u2 * u2;
    } while (x > 1);
    double y = sqrt(-2 * log(x) / x);
    z_ = u2 * y;
    return u1 * y;

}


#endif //FINANCE_NORMALINVERSEMARSAGLIABRAY_H

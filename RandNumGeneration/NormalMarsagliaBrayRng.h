//
// Created by CUI Shidong on 12/7/2016.
//

#ifndef FINANCE_NORMALINVERSEMARSAGLIABRAY_H
#define FINANCE_NORMALINVERSEMARSAGLIABRAY_H

#include <cmath>

template<typename UniformRNG>
class NormalMarsagliaBrayRng {
public:
    NormalMarsagliaBrayRng() : rng_() {
        z_ = 0.0;
        secondExists_ = false;
    }

    double next();

    double last() { return last_; }

private:
    UniformRNG rng_;
    double z_;           /**< second value of Marsaglia Bray scheme. */
    double last_;        /**< last return value. */
    bool secondExists_;

};

template<typename UniformRNG>
double NormalMarsagliaBrayRng<UniformRNG>::next() {

    if (secondExists_) {
        secondExists_ = !secondExists_;
        last_ = z_;
        return last_;
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
    last_ = u1 * y;
    return last_;
}


#endif //FINANCE_NORMALINVERSEMARSAGLIABRAY_H

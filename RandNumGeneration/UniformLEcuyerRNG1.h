//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_LECUYERUNIFORMRNG1_H
#define FINANCE_LECUYERUNIFORMRNG1_H

#include "Singleton.h"

class UniformLEcuyerRNG1 : public Singleton<UniformLEcuyerRNG1> {
public:

    friend class Singleton<UniformLEcuyerRNG1>;

    void setSeed(const long seed);

    double next();

    double last() { return u_; }

private:
    long seed_;
    double u_;

    explicit UniformLEcuyerRNG1(unsigned long seed = 7777);
};


#endif //FINANCE_LECUYERUNIFORMRNG1_H

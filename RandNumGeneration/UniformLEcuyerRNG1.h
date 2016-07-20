//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_LECUYERUNIFORMRNG1_H
#define FINANCE_LECUYERUNIFORMRNG1_H


class UniformLEcuyerRNG1 {
public:
    explicit UniformLEcuyerRNG1(unsigned long seed = 7777);

    void SetSeed(const long seed);

    double next();

private:
    long seed_;
};


#endif //FINANCE_LECUYERUNIFORMRNG1_H

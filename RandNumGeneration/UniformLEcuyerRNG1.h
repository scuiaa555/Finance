//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_LECUYERUNIFORMRNG1_H
#define FINANCE_LECUYERUNIFORMRNG1_H


class UniformLEcuyerRNG1 {
public:
    explicit UniformLEcuyerRNG1(unsigned long seed = 7777);

    void setSeed(const long seed);

    double next();

    double last() { return u_; }

private:
    long seed_;
    double u_;
};


#endif //FINANCE_LECUYERUNIFORMRNG1_H

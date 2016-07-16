//
// Created by CUI Shidong on 10/7/2016.
//

#include "UniformLEcuyerRNG1.h"

const unsigned long m = 2147483647;
const unsigned long a = 40692;
const unsigned long q = 52774;
const unsigned long r = 3791;
const double h = 1.0 / m;

UniformLEcuyerRNG1::UniformLEcuyerRNG1(unsigned long seed) : seed_(seed) { }

void UniformLEcuyerRNG1::SetSeed(const long seed) {
    seed_ = seed;
}

double UniformLEcuyerRNG1::next() {
    unsigned long k = seed_ / q;
    seed_ = a * (seed_ - k * q) - k * r;
    if (seed_ < 0) seed_ += m;
    return h * seed_;
}

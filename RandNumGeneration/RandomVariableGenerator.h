//
// Created by CUI Shidong on 15/12/2016.
//

#ifndef FINANCE_RANDOMVARIABLEGENERATOR_H
#define FINANCE_RANDOMVARIABLEGENERATOR_H

#include "Model.h"

class GenericRandomVariableGenerator {
public:
    GenericRandomVariableGenerator():dimension_(0) {}
    class Argument {
    public:
        virtual ~Argument() { }
    };
    unsigned long dimension_;
    virtual ~GenericRandomVariableGenerator() {}
};

template<typename T>
class RandomVariableGenerator : public GenericRandomVariableGenerator {
public:
//    typedef T rng_return_type;
    RandomVariableGenerator():GenericRandomVariableGenerator() {}

    virtual const T &next() = 0;

    virtual const T &last() = 0;

};

#endif //FINANCE_RANDOMVARIABLEGENERATOR_H

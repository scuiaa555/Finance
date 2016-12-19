//
// Created by CUI Shidong on 15/12/2016.
//

#ifndef FINANCE_RANDOMVARIABLEGENERATOR_H
#define FINANCE_RANDOMVARIABLEGENERATOR_H

#include "Model.h"

class GenericRandomVariableGenerator {
public:
    GenericRandomVariableGenerator() : dimension_(0) {}

    GenericRandomVariableGenerator(unsigned long dimension) : dimension_(dimension) {}

    unsigned long getDimension() const { return dimension_; }

    class Argument {
    public:
        virtual ~Argument() {}
    };

//    virtual GenericRandomVariableGenerator::Argument *getArgument()=0;

    virtual ~GenericRandomVariableGenerator() {}

protected:
    unsigned long dimension_;
};

template<typename returnType>
class RandomVariableGenerator : public GenericRandomVariableGenerator {
public:
//    typedef T rng_return_type;
    RandomVariableGenerator() : GenericRandomVariableGenerator() {}

    RandomVariableGenerator(unsigned long dimension);

    virtual const returnType &next() = 0;

    virtual const returnType &last() = 0;

};

template<typename returnType>
RandomVariableGenerator<returnType>::RandomVariableGenerator(unsigned long dimension):GenericRandomVariableGenerator(
        dimension) {}


#endif //FINANCE_RANDOMVARIABLEGENERATOR_H

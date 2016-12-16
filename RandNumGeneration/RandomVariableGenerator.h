//
// Created by CUI Shidong on 15/12/2016.
//

#ifndef FINANCE_RANDOMVARIABLEGENERATOR_H
#define FINANCE_RANDOMVARIABLEGENERATOR_H

#include "Model.h"

class GenericRandomVariableGenerator {
public:
    class Argument {
    public:
        virtual ~Argument() { }
    };
};

template<typename T>
class RandomVariableGenerator : public GenericRandomVariableGenerator {
public:

    virtual const T &next() = 0;

    virtual const T &last() = 0;

    virtual GenericRandomVariableGenerator::Argument *getArgument() { }
};

#endif //FINANCE_RANDOMVARIABLEGENERATOR_H

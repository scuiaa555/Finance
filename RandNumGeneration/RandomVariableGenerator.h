//
// Created by CUI Shidong on 15/12/2016.
//

#ifndef FINANCE_RANDOMVARIABLEGENERATOR_H
#define FINANCE_RANDOMVARIABLEGENERATOR_H

#include "Model.h"

template<typename T>
class RandomVariableGenerator {
public:

    virtual const T &next() = 0;

    virtual const T &last() = 0;

    virtual void getArgument(Model::Argument *arg) { }
};

#endif //FINANCE_RANDOMVARIABLEGENERATOR_H
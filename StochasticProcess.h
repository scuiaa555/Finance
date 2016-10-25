//
// Created by CUI Shidong on 27/6/2016.
//

#ifndef FINANCE_MODEL_H
#define FINANCE_MODEL_H


#include <memory>
#include "NameDef.h"
#include "Parameter.h"

class StochasticProcess {
public:
    class ParameterSet {
    };

    virtual Quote getSpot() const = 0;

    virtual ~StochasticProcess() { }
};




#endif //FINANCE_MODEL_H

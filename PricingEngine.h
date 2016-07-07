//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PRICING_ENGINE_H
#define FINANCE_PRICING_ENGINE_H

#include <memory>
#include "nameDef.h"
#include "Model.h"
//#include "Option.h"   must not include

class PricingEngine {
public:
    PricingEngine() { }

    virtual void calculate() = 0;

    /*
    //class Arguments : public Option::Arguments {
    //};*/

    class Arguments;

    /*class Results {
    public:
        Money price;
    };*/

    virtual Arguments *GetArguments() = 0;

//    virtual void validate() = 0;

    //std::shared_ptr<Results> results_;
    //std::shared_ptr<Arguments> arguments_;
};


class PricingEngine::Arguments {
public:
    Arguments() { }

    double a;

    virtual void print() { double a = 0; };

    //virtual ~Arguments() { }
};

template<typename ArgumentsType>
class GenericEngine : public PricingEngine {
public:
    GenericEngine() { }

    PricingEngine::Arguments *GetArguments() {
        return &arguments_;
    }

//protected:
    mutable ArgumentsType arguments_;

};

#endif //FINANCE_PRICING_ENGINE_H

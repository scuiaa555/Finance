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

    class Results;

    /*class Results {
    public:
        Money price;
    };*/

    virtual Arguments *GetArguments() const = 0;

    virtual Results *GetResults() const = 0;

//    virtual void validate() = 0;

    //std::shared_ptr<Results> results_;
    //std::shared_ptr<Arguments> arguments_;
};


class PricingEngine::Arguments {
public:
    Arguments() { }

//    double a;

//    virtual void print() { double a = 0; };

    virtual ~Arguments() { }
};

class PricingEngine::Results {
public:
    Results() { }

    virtual ~Results() { }
};

template<typename ArgumentsType, typename ResultsType>
class GenericEngine : public PricingEngine {
public:
    GenericEngine() { }

    PricingEngine::Arguments *GetArguments() const {
        return &arguments_;
    }

    PricingEngine::Results *GetResults() const {
        return &results_;
    }

//protected:
    mutable ArgumentsType arguments_;
    mutable ResultsType results_;

};

#endif //FINANCE_PRICING_ENGINE_H

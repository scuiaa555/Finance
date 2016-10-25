//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PRICING_ENGINE_H
#define FINANCE_PRICING_ENGINE_H

#include <memory>
#include "NameDef.h"
#include "StochasticProcess.h"
//#include "Option.h"   must not be included

class PricingEngine {
public:
    PricingEngine() { }

    virtual void calculate() = 0;

    class Arguments;

    class Results;

//    class Results {
//    public:
//        Money price;
//    };

    virtual Arguments *getArguments() const = 0;

    virtual Results *getResults() const = 0;

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

    PricingEngine::Arguments *getArguments() const override {  // mutable below
        return &arguments_;
    }

    PricingEngine::Results *getResults() const override {
        return &results_;
    }

//protected:
    mutable ArgumentsType arguments_;
    mutable ResultsType results_;

};

#endif //FINANCE_PRICING_ENGINE_H

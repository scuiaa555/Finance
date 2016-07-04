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
    virtual void calculate() = 0;

    /*
    //class Arguments : public Option::Arguments {
    //};*/

    class Arguments;

    /*class Results {
    public:
        Money price;
    };*/

    virtual std::shared_ptr<Arguments> GetArguments() = 0;

    //std::shared_ptr<Results> results_;
    std::shared_ptr<Arguments> arguments_;
};

class AnalyticBSEngine : public PricingEngine {
public:
    AnalyticBSEngine(std::shared_ptr<BSModel> model);

    double test(double a) { return a; }

    void calculate() override;

/*    class AnalyticBSResults : public virtual PricingEngine::Results {
    public:
        double delta;
    };

    class AnalyticBSArguments : public virtual PricingEngine::Arguments {
    public:
        std::shared_ptr<Payoff> payoff_;
    };*/

private:
    std::shared_ptr<BSModel> model_;
    //std::shared_ptr<AnalyticBSEngine::AnalyticBSResults> results_;
    //std::shared_ptr<AnalyticBSEngine::Arguments> arguments_;
};

class PricingEngine::Arguments {
public:
    double a;

    virtual void print() { double a = 0; };

    //virtual ~Arguments() { }
};

/*template<typename ArgumentsType>
class GenericEngine : public PricingEngine {
public:
    std::shared_ptr<PricingEngine::Arguments> GetArguments() const {
        return arguments_;
    }

protected:
    mutable std::shared_ptr<ArgumentsType> arguments_;

};*/

#endif //FINANCE_PRICING_ENGINE_H

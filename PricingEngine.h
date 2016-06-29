//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PRICING_ENGINE_H
#define FINANCE_PRICING_ENGINE_H

#include <memory>
#include "nameDef.h"
#include "Model.h"
#include "Option.h"

class PricingEngine {
public:
    /*virtual void calculate() = 0;

    //class Arguments : public Option::Arguments {
    //};

    class Arguments {
        double a;
    };

    class Results {
    public:
        Money price;
    };*/

    //virtual void GetArguments(std::shared_ptr<Option::Arguments> arguments);

    //std::shared_ptr<Results> results_;
    //std::shared_ptr<PricingEngine::Arguments> arguments_;
};

class AnalyticBSEngine : public PricingEngine {
public:
    AnalyticBSEngine(std::shared_ptr<BSModel> model);

    //void calculate() override;

    class AnalyticBSResults : public virtual PricingEngine::Results {
    public:
        double delta;
    };

    class AnalyticBSArguments : public virtual PricingEngine::Arguments {
    public:
        std::shared_ptr<Payoff> payoff_;
    };

private:
    std::shared_ptr<BSModel> model_;
    //std::shared_ptr<AnalyticBSEngine::AnalyticBSResults> results_;
    //std::shared_ptr<AnalyticBSEngine::Arguments> arguments_;
};


#endif //FINANCE_PRICING_ENGINE_H

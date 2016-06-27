//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PRICING_ENGINE_H
#define FINANCE_PRICING_ENGINE_H

#include <memory>
#include "nameDef.h"

class PricingEngine {
public:
    virtual void calculate() = 0;

    class Results {
    public:
        Money price;
    };
};

class AnalyticBSEngine : public PricingEngine {
public:
    void calculate() override;

    class AnalyticBSResults : public virtual PricingEngine::Results {
    public:
        double delta;
    };

private:
    std::shared_ptr<Model> model_;
    std::shared_ptr<PricingEngine::Results> results_;
};


#endif //FINANCE_PRICING_ENGINE_H

//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_OPTION_H
#define FINANCE_OPTION_H

#include "nameDef.h"
#include "Payoff.h"
#include "PricingEngine.h"
#include <memory>

class Option {
public:
    Option() { }

    virtual Time GetMaturity() const = 0;
    void SetPricingEngine(std::shared_ptr<PricingEngine> pricingEngine);

private:
    std::shared_ptr<PricingEngine> pricingEngine_;
};

class EuropeanCall : public Option {
public:
    EuropeanCall() { }

    EuropeanCall(Time Maturity, std::shared_ptr<Payoff> payoff);

    EuropeanCall(Time Maturity, Quote Strike);

    Time GetMaturity() const override;


private:
    std::shared_ptr<Payoff> payoff_;
    Time Maturity_;
};

#endif //FINANCE_OPTION_H

//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_OPTION_H
#define FINANCE_OPTION_H

#include "nameDef.h"
#include "Payoff.h"
#include <memory>
#include <string>

//class PricingEngine;

//class PricingEngine::Arguments;

class Option {
public:
    Option() { }

    //virtual Time GetMaturity() const = 0;

    //void SetPricingEngine(std::shared_ptr<PricingEngine> pricingEngine);

    //Money npv();

    //void Calculate();

    //virtual void GetArguments() = 0;

    //class Arguments : public PricingEngine::Arguments {
    //};
    //class Arguments;

protected:
    //std::shared_ptr<PricingEngine> pricingEngine_;
};

class EuropeanCall : public Option {
public:
    EuropeanCall() { }

    EuropeanCall(Time Maturity, std::shared_ptr<Payoff> payoff);

    EuropeanCall(Time Maturity, Quote Strike);

    //Time GetMaturity() const override;

    //void GetArguments() override;

    class EuropeanCallArguments;


private:
    std::shared_ptr<Payoff> payoff_;
    Time Maturity_;
};

#endif //FINANCE_OPTION_H
